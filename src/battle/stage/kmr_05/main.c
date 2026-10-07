#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
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
    .bg = "kmr_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// kmr_05:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(EnableModel, MODEL_yuka, false)
    Call(EnableModel, MODEL_o303, false)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "kmr_tex",
    .bg = "kmr_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
