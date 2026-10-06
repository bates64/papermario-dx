#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/isk_bt03_shape.h"

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
    .texture = "isk_tex",
    .shape = "isk_bt03_shape",
    .hit = "isk_bt03_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
