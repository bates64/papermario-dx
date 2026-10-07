#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/omo_bt02_shape.h"

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
    .shape = "omo_bt02_shape",
    .hit = "omo_bt02_hit",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
