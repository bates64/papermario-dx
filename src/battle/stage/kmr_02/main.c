#include "battle/battle.h"
#include "script_api/battle.h"

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
    .texture = "kmr_tex",
    .shape = "kmr_bt02_shape", //@bug does not exist
    .bg = "kmr_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
