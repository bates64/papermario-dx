#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/nok_bt03_shape.h"

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
    MODEL_ha3,
    MODEL_hap,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "nok_tex",
    .shape = "nok_bt03_shape",
    .hit = "nok_bt03_hit",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
