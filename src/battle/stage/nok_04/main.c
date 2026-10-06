#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/nok_bt04_shape.h"

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
    MODEL_ueki2,
    MODEL_ueki1,
    MODEL_kabu2,
    MODEL_kabu1,
    MODEL_kusa3,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "nok_tex",
    .shape = "nok_bt04_shape",
    .hit = "nok_bt04_hit",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
