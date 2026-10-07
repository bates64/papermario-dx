#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/omo_03_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g97, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "omo_tex",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};

// omo_03:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "omo_tex",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
};
