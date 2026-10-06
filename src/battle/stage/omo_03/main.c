#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/omo_bt03_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g97, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "omo_tex",
    .shape = "omo_bt03_shape",
    .hit = "omo_bt03_hit",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
