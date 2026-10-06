#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kpa_bt01_shape.h"

// blue torches
EvtScript EVS_TexAnim_Fire = {
    Set(LVarA, LVar0)
    Call(SetTexPanner, LVarA, TEX_PANNER_1)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Loop(0)
        Call(SetTexPanOffset, TEX_PANNER_1, TEX_PANNER_MAIN, LVar0, LVar1)
        Add(LVar0, 0x8000)
        Add(LVar1, 0)
        Wait(5)
    EndLoop
    Return
    End
};

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_switch, MODEL_GROUP_HIDDEN)
    Thread
        Set(LVar0, MODEL_o416)
        Exec(EVS_TexAnim_Fire)
        Wait(5)
        Set(LVar0, MODEL_o418)
        Exec(EVS_TexAnim_Fire)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o383,
    MODEL_o382,
    MODEL_o381,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "kpa_tex",
    .shape = "kpa_bt01_shape",
    .hit = "kpa_bt01_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
