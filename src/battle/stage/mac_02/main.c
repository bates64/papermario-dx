#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

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
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
