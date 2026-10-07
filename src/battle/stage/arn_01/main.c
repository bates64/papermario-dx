#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/arn_01_shape.h"

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
    -1,
    MODEL_iwa4,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "arn_tex",
    .bg = "arn_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
