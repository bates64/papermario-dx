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

BATTLE_STAGE_ENTRY = {
    .texture = "isk_tex",
    .shape = "isk_bt00_shape", //@bug this does not exist!
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
