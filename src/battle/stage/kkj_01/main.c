#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kkj_bt01_shape.h"

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
    MODEL_hana,
    MODEL_ha1,
    MODEL_ha2,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kkj_tex",
    .shape = "kkj_bt01_shape",
    .hit = "kkj_bt01_hit",
    .bg = "kpa_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
