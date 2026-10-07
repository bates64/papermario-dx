#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/dgb_bt01_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "dgb_tex",
    .shape = "dgb_bt01_shape",
    .hit = "dgb_bt01_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
