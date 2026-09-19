#include "foliage.h"
#include "npc.h"
#include "model.h"
#include "effects.h"

// how many times to shake LEFT-RIGHT before stopping
#define SHAKE_CYCLES 5

// ShakeTree and SearchBush can be invoked from battle
API_CALLABLE(GetActorPos);

static void foliage_setup_shear_mtx(Matrix4f mtx, f32 scale, f32 xAmount, f32 zAmount) {
    guMtxIdentF(mtx);
    mtx[1][0] = scale * xAmount;
    mtx[1][1] = 1.0f;
    mtx[1][2] = scale * zAmount;
}

static void foliage_apply_model_shear(s32 modelID, f32 scale, f32 dx, f32 pivotY, f32 dz) {
    s32 modelListIndex = get_model_list_index_from_tree_index(modelID);
    Model* model = get_model_from_list_index(modelListIndex);
    Matrix4f mtx;

    if (!model) {
        return;
    }

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        guTranslateF(model->userTransformMtx, 0.0f, pivotY, 0.0f);
        foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -pivotY, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    } else {
        guTranslateF(mtx, 0.0f, pivotY, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -pivotY, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
    }
}

static void foliage_clear_model_shear(s32 modelID) {
    s32 modelListIndex = get_model_list_index_from_tree_index(modelID);
    Model* model = get_model_from_list_index(modelListIndex);

    if (!model) {
        return;
    }

    guMtxIdentF(model->userTransformMtx);

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    }
}

API_CALLABLE(ShakeFoliageModels) {
    Bytecode* args = script->ptrReadPos;

    FoliageModelList* list = (FoliageModelList*) evt_get_variable(script, *args++);
    s32 soundID = evt_get_variable(script, *args++);
    f32 scale = evt_get_float_variable(script, *args++);
    f32 dx = evt_get_float_variable(script, *args++);
    f32 pivotY = evt_get_float_variable(script, *args++);

    enum {
        SHAKE_LEFT  = 0,
        SHAKE_RIGHT = 1,
        SHAKE_DONE  = 2,
    };

    if (isInitialCall) {
        script->functionTemp[0] = SHAKE_LEFT;
        script->functionTemp[1] = 0; // cyclesDone
    }

    // do nothing for empty or missing model list
    if (list == NULL || list->count <= 0) {
        return ApiStatus_DONE2;
    }

    switch (script->functionTemp[0]) {
        case SHAKE_LEFT: {
            for (s32 i = 0; i < list->count; i++) {
                s32 modelID = list->models[i];
                foliage_apply_model_shear(modelID, scale, dx, pivotY, 0.0f);

                // only play sound ONCE, for the first model on the first iteration
                if (script->functionTemp[1] == 0 && i == 0) {
                    f32 x, y, z;
                    f32 sx, sy, sz;

                    s32 modelListIndex = get_model_list_index_from_tree_index(modelID);
                    get_model_center_and_size(modelID, &x, &y, &z, &sx, &sy, &sz);
                    sfx_play_sound_at_position(soundID, SOUND_SPACE_DEFAULT, x, y, z);
                }
            }
            script->functionTemp[0] = SHAKE_RIGHT;
            return ApiStatus_BLOCK;
        }

        case SHAKE_RIGHT: {
            for (s32 i = 0; i < list->count; i++) {
                s32 modelID = list->models[i];
                foliage_apply_model_shear(modelID, scale, -dx, pivotY, 0.0f);
            }

            script->functionTemp[1]++; // cyclesDone++

            if (script->functionTemp[1] < SHAKE_CYCLES) {
                script->functionTemp[0] = SHAKE_LEFT;
            } else {
                script->functionTemp[0] = SHAKE_DONE;
            }
            return ApiStatus_BLOCK;
        }

        case SHAKE_DONE: {
            for (s32 i = 0; i < list->count; i++) {
                s32 modelID = list->models[i];
                foliage_clear_model_shear(modelID);
            }
            // all done
            return ApiStatus_DONE2;
        }

        default:
            return ApiStatus_DONE2;
    }
}

API_CALLABLE(SpawnFoliageDrops) {
    Bytecode* args = script->ptrReadPos;
    FoliageDropList* list = (FoliageDropList*) evt_get_variable(script, *args++);

    if (!list) {
        return ApiStatus_DONE2;
    }

    for (s32 i = 0; i < list->count; i++) {
        FoliageDrop* drop = &list->drops[i];

        if (drop->spawnFlag == 0) {
            make_item_entity_nodelay(drop->itemID,
                drop->pos.x, drop->pos.y, drop->pos.z,
                drop->spawnMode, drop->pickupFlag);
        } else {
            b32 alreadySpawned = evt_get_variable(script, drop->spawnFlag);
            if (!alreadySpawned) {
                evt_set_variable(script, drop->spawnFlag, true);
                make_item_entity_nodelay(drop->itemID,
                    drop->pos.x, drop->pos.y, drop->pos.z,
                    drop->spawnMode, drop->pickupFlag);
            }
        }
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SpawnShakeTreeFX) {
    Bytecode* args = script->ptrReadPos;
    FoliageVectorList* list = (FoliageVectorList*) evt_get_variable(script, *args++);
    s32 treeType = evt_get_variable(script, *args++);

    if (!list) {
        return ApiStatus_DONE2;
    }

    for (s32 i = 0; i < list->count; i++) {
        Vec3i* pos = &list->vectors[i];

        switch(treeType) {
            case TREE_TYPE_STANDARD:
                fx_drop_leaves(0, pos->x, pos->y, pos->z, 100);
                break;
            case TREE_TYPE_SPARKLY:
                fx_sparkles(2, pos->x, pos->y, pos->z, 50);
                fx_sparkles(2, pos->x, pos->y, pos->z, 50);
                break;
        }
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_SearchBush = {
    // get player Y to find bottom of bush
    Call(GetGameContext, LVarF)
    IfEq(LVarF, CONTEXT_BATTLE)
        Call(GetActorPos, ACTOR_PLAYER, LVar1, LVarF, LVar2)
    Else
        Call(GetPlayerPos, LVar1, LVarF, LVar2)
    EndIf
    // read SearchBushConfig
    UseBuf(LVar0)
    BufRead4(LVar1, LVar2, LVar3, LVar4) // bush models, drops, vectors, callback
    BufRead1(LVar5) // bush type
    Thread
        Call(ShakeFoliageModels, LVar1, SOUND_SEARCH_BUSH, Float(0.1), Float(1.0), LVarF)
    EndThread
    Thread
        Call(SpawnFoliageDrops, LVar2)
    EndThread
    Wait(15)
    IfNe(LVar4, 0) // has callback?
        ExecWait(LVar4)
    EndIf
    Return
    End
};

EvtScript EVS_ShakeTree = {
    SetTimescale(Float(2.0))
    // get player Y to find bottom of tree
    Call(GetGameContext, LVarF)
    IfEq(LVarF, CONTEXT_BATTLE)
        Call(GetActorPos, ACTOR_PLAYER, LVar1, LVarF, LVar2)
    Else
        Call(GetPlayerPos, LVar1, LVarF, LVar2) // get player Y (ignore X and Z)
    EndIf
    // read ShakeTreeConfig
    UseBuf(LVar0)
    BufRead4(LVar1, LVar2, LVar3, LVar4) // leaf models, trunk models, drops, vectors
    BufRead2(LVar5, LVar6) // callback, tree type
    Thread
        Call(ShakeFoliageModels, LVar1, SOUND_SHAKE_TREE_LEAVES, Float(0.1), Float(0.2), LVarF)
    EndThread
    Thread
        Call(ShakeFoliageModels, LVar2, SOUND_SMACK_TREE, Float(0.1), Float(0.2), LVarF)
    EndThread
    Thread
        Call(SpawnFoliageDrops, LVar3)
    EndThread
    Thread
        Call(SpawnShakeTreeFX, LVar4, LVar6)
    EndThread
    IfNe(LVar5, 0) // has callback?
        ExecWait(LVar5)
    EndIf
    Wait(15)
    Return
    End
};
