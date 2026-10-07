#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

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
    .bg = "sbk3_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};

// isk_03:b

OVL_DEF_STAGE(b) = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
