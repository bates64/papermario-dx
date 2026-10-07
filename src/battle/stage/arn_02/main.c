#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

EvtScript EVS_RotateWindmill = {
    Set(LVarA, LVar0)
    Set(LVar0, 0)
    Label(0)
        Add(LVar0, 1)
        IfGt(LVar0, 359)
            Sub(LVar0, 360)
        EndIf
        Call(RotateModel, LVarA, LVar0, 0, 0, 1)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Set(LVar0, MODEL_o332)
    ExecWait(EVS_RotateWindmill)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    -1,
    MODEL_iwa4,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "arn_tex",
    .bg = "arn_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
