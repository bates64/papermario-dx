#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/dgb_bt03_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "dgb_tex",
    .shape = "dgb_bt03_shape",
    .hit = "dgb_bt03_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
