#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "pra_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};

// pra_03:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g115, MODEL_GROUP_HIDDEN)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "pra_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
};

// pra_03:c

EvtScript EVS_PreBattle_c = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g115, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_g117, MODEL_GROUP_HIDDEN)
    Return
    End
};

OVL_DEF_STAGE(c) = {
    .texture = "pra_tex",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
};
