#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/mac_bt02_shape.h"

#define NAMESPACE A(mac_02)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableBattleFloorReflections, true)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Call(EnableBattleFloorReflections, false)
    Return
    End
};

Stage NAMESPACE = {
    .texture = "mac_tex",
    .module = "areas/mac/mac_bt02",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
