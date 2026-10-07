#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
#include "battle/stage/common/MovingClouds.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Set(LVar0, MODEL_g65)
    Set(LVar2, 0)
    Exec(EVS_AnimateCloud)
    Set(LVar0, MODEL_g62)
    Set(LVar2, 70)
    Set(LVar3, 175)
    Set(LVar4, -170)
    Exec(EVS_AnimateCloud_WithOffset2D)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_saku,
    MODEL_kabe2,
    MODEL_kabe,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "trd_tex",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
