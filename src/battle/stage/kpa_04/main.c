#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/kpa_04_shape.h"

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
    Call(SetGroupVisibility, MODEL_g3, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_wa, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_kusari, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_g4, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi3, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi4, MODEL_GROUP_HIDDEN)
    Set(LVar0, MODEL_o450)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_o451)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_o454)
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
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};

// kpa_04:b

// blue torches
EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_wa, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_kusari, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi3, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_hi4, MODEL_GROUP_HIDDEN)
    Set(LVar0, MODEL_o450)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_o451)
    Exec(EVS_TexAnim_Fire)
    Set(LVar0, MODEL_o454)
    Exec(EVS_TexAnim_Fire)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "kpa_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
};

// kpa_04:c

// blue torches
EvtScript EVS_PreBattle_c = {
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

OVL_DEF_STAGE(c) = {
    .texture = "kpa_tex",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
};
