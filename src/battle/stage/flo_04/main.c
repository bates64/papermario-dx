#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/flo_bt04_shape.h"

EvtScript EVS_AnimateCloud = {
    Set(LVarA, LVar0)
    Set(LVarF, 0)
    Loop(0)
        Call(CosInterpMinMax, LVarF, LVar0, Float(0.968), Float(1.031), 15, 0, 0)
        Call(CosInterpMinMax, LVarF, LVar1, Float(1.031), Float(0.968), 15, 0, 0)
        Call(ScaleModel, LVarA, LVar1, LVar0, 1)
        Add(LVarF, 1)
        IfGe(LVarF, 30)
            Set(LVarF, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

#include "battle/stage/common/MakeSun.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_o412)
    Exec(EVS_AnimateCloud)
    Set(LVar0, MODEL_o413)
    Exec(EVS_AnimateCloud)
    Set(LVar0, MODEL_o414)
    Exec(EVS_AnimateCloud)
    Set(LVar0, MODEL_o415)
    Exec(EVS_AnimateCloud)
    Set(LVar0, MODEL_o419)
    Exec(EVS_AnimateCloud)
    Thread
        Set(LVar0, MODEL_o431)
        Exec(EVS_AnimateCloud)
        Set(LVar0, MODEL_o432)
        Exec(EVS_AnimateCloud)
        Wait(5)
        Set(LVar0, MODEL_b2_2)
        Exec(EVS_AnimateCloud)
        Set(LVar0, MODEL_b2_1)
        Exec(EVS_AnimateCloud)
        Wait(5)
        Set(LVar0, MODEL_b1_2)
        Exec(EVS_AnimateCloud)
        Set(LVar0, MODEL_b1_1)
        Exec(EVS_AnimateCloud)
        Set(LVar0, MODEL_b1_3)
        Exec(EVS_AnimateCloud)
        Wait(5)
        Set(LVar0, MODEL_o433)
        Exec(EVS_AnimateCloud)
        Set(LVar0, MODEL_o434)
        Exec(EVS_AnimateCloud)
    EndThread
    Call(CloneModel, MODEL_o427, CLONED_MODEL(0))
    Call(EnableModel, CLONED_MODEL(0), false)
    Call(TranslateModel, CLONED_MODEL(0), 0, 9, 0)
    Call(ParentColliderToModel, 0, CLONED_MODEL(0))
    ExecWait(MakeSun)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    -1,
    MODEL_o431,
    MODEL_o419,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "flo_tex",
    .shape = "flo_bt04_shape",
    .hit = "flo_bt04_hit",
    .bg = "sra_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
