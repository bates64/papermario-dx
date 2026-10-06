#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kmr_bt05_shape.h"

#include "battle/stage/common/MovingClouds.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(EnableModel, MODEL_o302, false)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_n2,
    MODEL_m4,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kmr_tex",
    .shape = "kmr_bt05_shape",
    .hit = "kmr_bt05_hit",
    .bg = "kmr_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
