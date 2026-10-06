#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("eldstar", BTL_POS_AIR_C, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "nok_01", "Star Spirit Tutorial"),
    {},
};

static StageList Stages = {
    STAGE("nok_01", "nok_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
