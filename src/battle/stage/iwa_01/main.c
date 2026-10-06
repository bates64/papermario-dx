#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/iwa_bt01_shape.h"

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

BATTLE_STAGE_ENTRY = {
    .texture = "iwa_tex",
    .shape = "iwa_bt01_shape",
    .hit = "iwa_bt01_hit",
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
    ACTOR_BY_POS(whacka, WhackaPos, 0),
};

#include "battle/stage/common/whacka.inc.c"
