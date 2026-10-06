#include "battle/battle.h"
#include "script_api/battle.h"

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
    .texture = "omo_tex",
    .shape = "omo_bt07_shape",
    .hit = "omo_bt07_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
