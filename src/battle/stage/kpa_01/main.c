#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

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

OVL_DEF_STAGE() = {
    .texture = "kpa_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// kpa_01:b

// blue torches
EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_hasira, MODEL_GROUP_HIDDEN)
    Set(LVar0, MODEL_o416)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_o418)
    Exec(EVS_TexAnim_Fire)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "kpa_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
