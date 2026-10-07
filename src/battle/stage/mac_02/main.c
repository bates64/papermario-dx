#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/mac_bt02_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableBattleFloorReflections, true)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Call(EnableBattleFloorReflections, false)
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "mac_tex",
    .shape = "mac_bt02_shape",
    .hit = "mac_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
