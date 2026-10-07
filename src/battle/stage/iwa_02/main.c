#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/iwa_02_shape.h"

// this (unused) whacka is part of the stage
extern ActorBlueprint whacka;

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
    MODEL_o331,
    MODEL_iwa1,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "iwa_tex",
    .bg = "iwa_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

Vec3i OriginPos = { 0, 0, 0 };

Formation WhackaFormation = {
    RAW_ACTOR_BY_POS(whacka, OriginPos, 0),
};

#include "battle/stage/common/whacka.inc.c"
