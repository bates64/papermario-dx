#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kpa_bt04_shape.h"

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
    Call(SetGroupVisibility, MODEL_o415, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_o453, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_o452, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_o454, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_o451, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_o450, MODEL_GROUP_HIDDEN)
    Set(LVar0, MODEL_hi1)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_hi2)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_hi3)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_hi4)
    Exec(EVS_TexAnim_Fire)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "kpa_tex",
    .shape = "kpa_bt04_shape",
    .hit = "kpa_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
