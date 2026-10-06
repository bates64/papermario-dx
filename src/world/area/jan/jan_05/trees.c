#include "jan_05.h"
#include "foliage.h"

API_CALLABLE(IsJungleFuzzyPresent) {
    if (get_enemy_safe(NPC_JungleFuzzy) == nullptr) {
        script->varTable[0] = false;
    } else {
        script->varTable[0] = true;
    }
    return ApiStatus_DONE2;
}

EvtScript EVS_OnShakeTree1 = {
    Wait(15)
    Call(IsJungleFuzzyPresent)
    IfEq(LVar0, true)
        Call(SetNpcVar, NPC_JungleFuzzy, 7, 1)
    EndIf
    Return
    End
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o95, MODEL_o96, MODEL_o97, MODEL_o98, MODEL_o99);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o94);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { 87.0f, 114.0f, -390.0f },
        { 172.0f, 114.0f, -400.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
    .callback = &EVS_OnShakeTree1,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 127.0f, 0.0f, -420.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o89, MODEL_o90, MODEL_o91, MODEL_o92, MODEL_o93);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o88);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 400, 100, -145 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN05_Tree2_Coin,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 402.0f, 114.0f, -135.0f },
        { 487.0f, 114.0f, -145.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 442.0f, 0.0f, -165.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o83, MODEL_o84, MODEL_o85, MODEL_o86, MODEL_o87);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o34);

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { -309.0f, 112.0f, -301.0f },
        { -226.0f, 105.0f, -306.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .vectors = &Tree3_Effects,
};

BombTrigger BombPos_Tree3 = {
    .pos = { -270.0f, 0.0f, -310.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o187, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o188, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o87, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
