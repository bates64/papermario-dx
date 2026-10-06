#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/arn_bt06_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_kabe3,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "arn_tex",
    .shape = "arn_bt06_shape",
    .hit = "arn_bt06_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
