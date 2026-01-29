#include "foliage.hpp"

namespace foliage {

void setup_shear_mtx(Matrix4f mtx, f32 scale, f32 xAmount, f32 zAmount) {
    guMtxIdentF(mtx);
    mtx[1][0] = scale * xAmount;
    mtx[1][1] = 1.0f;
    mtx[1][2] = scale * zAmount;
}

/// @apiparam int model ID
/// @apiparam float scale
/// @apiparam float dx
/// @apiparam float dy
/// @apiparam float dz
API_CALLABLE(TransformFoliage) {
    Bytecode* args = script->ptrReadPos;
    s32 modelListIndex = get_model_list_index_from_tree_index(evt_get_variable(script, *args++));
    f32 scale = evt_get_float_variable(script, *args++);
    f32 dx = evt_get_float_variable(script, *args++);
    f32 dy = evt_get_float_variable(script, *args++);
    f32 dz = evt_get_float_variable(script, *args++);
    Model* model = get_model_from_list_index(modelListIndex);
    Matrix4f mtx;

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        guTranslateF(model->userTransformMtx, 0.0f, dy, 0.0f);
        setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    } else {
        guTranslateF(mtx, 0.0f, dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_SearchBush = {
    UseBuf(LVar0) // SearchBushConfig
    BufRead4(LVar1, LVar2, LVar3, LVar4) // bush, drops, vectors, callback
    Call(GetPlayerPos, LVar5, LVarF, LVar7)
    Thread
        Set(LFlag0, false)
        IfNe(LVar1, 0)
            Loop(5)
                UseBuf(LVar1) // FoliageVectorList bush
                BufRead1(LVar2) // count
                BufRead1(LVarD) // vectors
                UseBuf(LVarD) // *vectors
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TransformFoliage, LVar3, Float(0.1), 1, LVarF, 0)
                    IfEq(LFlag0, false)
                        Set(LFlag0, true)
                        Call(PlaySoundAtModel, LVar3, SOUND_SEARCH_BUSH, SOUND_SPACE_DEFAULT)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar1) // FoliageVectorList bush
                BufRead1(LVar2) // count
                BufRead1(LVarD) // vectors
                UseBuf(LVarD) // *vectors
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TransformFoliage, LVar3, Float(0.1), -1, LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar1) // FoliageVectorList bush
            BufRead1(LVar2) // count
            BufRead1(LVarD) // vectors
            UseBuf(LVarD) // *vectors
            Loop(LVar2)
                BufRead1(LVar3)
                Call(TranslateModel, LVar3, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        IfNe(LVar2, 0)
            UseBuf(LVar2) // FoliageDropList drops
            BufRead1(LVar3) // count
            BufRead1(LVarD) // vectors
            UseBuf(LVarD) // *vectors
            Loop(LVar3)
                BufRead1(LVar4)
                BufRead3(LVar5, LVar6, LVar7)
                BufRead3(LVar8, LVar9, LVarA)
                IfEq(LVarA, 0)
                    Call(DropItemEntity, LVar4, LVar5, LVar6, LVar7, LVar8, LVar9)
                Else
                    Call(GetValueByRef, LVarA, LVarB)
                    IfEq(LVarB, 0)
                        Call(SetValueByRef, LVarA, 1)
                        Call(DropItemEntity, LVar4, LVar5, LVar6, LVar7, LVar8, LVar9)
                    EndIf
                EndIf
            EndLoop
        EndIf
    EndThread
    Wait(15)
    IfNe(LVar4, 0)
        ExecWait(LVar4)
    EndIf
    Return
    End
};

EvtScript EVS_ShakeTree = {
    SetTimescale(Float(2.0))
    UseBuf(LVar0) // ShakeTreeConfig
    BufRead4(LVar1, LVar2, LVar3, LVar4) // leaves, trunk, drops, vectors
    BufRead1(LVar5) // callback
    Call(GetPlayerPos, LVar6, LVarF, LVar8)
    //Call(PlaySound, SOUND_SMACK_TREE)
    //Call(PlaySound, SOUND_SHAKE_TREE_LEAVES)
    Thread
        Set(LFlag0, false)
        IfNe(LVar1, 0)
            Wait(1)
            Loop(5)
                UseBuf(LVar1) // FoliageModelList leaves
                BufRead1(LVar2) // count
                BufRead1(LVarD) // models
                UseBuf(LVarD) // *models
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TransformFoliage, LVar3, Float(0.1), Float(0.2), LVarF, 0)
                    IfEq(LFlag0, false)
                        Set(LFlag0, true)
                        Call(PlaySoundAtModel, LVar3, SOUND_SHAKE_TREE_LEAVES, SOUND_SPACE_DEFAULT)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar1) // FoliageModelList leaves
                BufRead1(LVar2) // count
                BufRead1(LVarD) // models
                UseBuf(LVarD) // *models
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TransformFoliage, LVar3, Float(0.1), Float(-0.2), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar1) // FoliageModelList leaves
            BufRead1(LVar2) // count
            BufRead1(LVarD) // models
            UseBuf(LVarD) // *models
            Loop(LVar2)
                BufRead1(LVar3)
                Call(TranslateModel, LVar3, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        Set(LFlag0, false)
        IfNe(LVar2, 0)
            Loop(5)
                UseBuf(LVar2) // FoliageModelList trunk
                BufRead1(LVar3) // count
                BufRead1(LVarD) // models
                UseBuf(LVarD) // *models
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TransformFoliage, LVar4, Float(0.1), Float(0.2), LVarF, 0)
                    IfEq(LFlag0, false)
                        Set(LFlag0, true)
                        Call(PlaySoundAtModel, LVar4, SOUND_SMACK_TREE, SOUND_SPACE_DEFAULT)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar2) // FoliageModelList trunk
                BufRead1(LVar3) // count
                BufRead1(LVarD) // models
                UseBuf(LVarD) // *models
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TransformFoliage, LVar4, Float(0.1), Float(-0.2), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar2) // FoliageModelList trunk
            BufRead1(LVar3) // count
            BufRead1(LVarD) // models
            UseBuf(LVarD) // *models
            Loop(LVar3)
                BufRead1(LVar4)
                Call(TranslateModel, LVar4, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        IfNe(LVar3, 0)
            UseBuf(LVar3) // FoliageDropList drops
            BufRead1(LVar4) // count
            BufRead1(LVarD) // drops
            UseBuf(LVarD) // *drops
            Loop(LVar4)
                BufRead1(LVar5)
                BufRead3(LVar6, LVar7, LVar8)
                BufRead3(LVar9, LVarA, LVarB)
                IfEq(LVarB, 0)
                    Call(DropItemEntity, LVar5, LVar6, LVar7, LVar8, LVar9, LVarA)
                Else
                    Call(GetValueByRef, LVarB, LVarC)
                    IfEq(LVarC, 0)
                        Call(SetValueByRef, LVarB, 1)
                        Call(DropItemEntity, LVar5, LVar6, LVar7, LVar8, LVar9, LVarA)
                    EndIf
                EndIf
            EndLoop
        EndIf
    EndThread
    Thread
        IfNe(LVar4, 0)
            UseBuf(LVar4) // FoliageDropList vectors
            BufRead1(LVar5) // count
            BufRead1(LVarD) // vectors
            UseBuf(LVarD) // *vectors
            Loop(LVar5)
                BufRead3(LVar6, LVar7, LVar8) // x y z
                PlayEffect(EFFECT_DROP_LEAVES, 0, LVar6, LVar7, LVar8, 100)
            EndLoop
        EndIf
    EndThread
    IfNe(LVar5, 0)
        ExecWait(LVar5)
    EndIf
    Wait(15)
    Return
    End
};

}; // namespace foliage
