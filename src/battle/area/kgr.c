#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("fuzzipede", BTL_POS_GROUND_C, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kgr_01", "Fuzzipede"),
    {},
};

static StageList Stages = {
    STAGE("kgr_01", "kgr_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
