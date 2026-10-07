#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/kmr_04_shape.h"
#include "battle/stage/common/MovingClouds.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Set(LVar0, MODEL_g60)
    Set(LVar2, 0)
    Exec(EVS_AnimateCloud)
    Set(LVar0, MODEL_g61)
    Set(LVar2, 70)
    Exec(EVS_AnimateCloud)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_m4,
    MODEL_n2,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kmr_tex",
    .bg = "kmr_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
