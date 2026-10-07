#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/iwa_01_shape.h"

// this (unused) whacka is part of the stage
extern ActorBlueprint whacka;
extern Formation WhackaFormation;

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetGroupVisibility, MODEL_b, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_iwa1,
    MODEL_o331,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "iwa_tex",
    .bg = "iwa_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
    .stageEnemyCount = 1,
    .stageFormation = &WhackaFormation,
    .stageEnemyChance = 512,
};

Vec3i WhackaPos = { 116, 0, -30 };

Formation WhackaFormation = {
    RAW_ACTOR_BY_POS(whacka, WhackaPos, 0),
};

#include "battle/stage/common/whacka.inc.c"

// iwa_01:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetGroupVisibility, MODEL_a, MODEL_GROUP_HIDDEN)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "iwa_tex",
    .bg = "iwa_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
