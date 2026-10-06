#include "battle/battle.h"

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("general_guy", BTL_POS_GROUND_C, 70),
    OVL_ACTOR_NAMED_BY_IDX("general_guy", toy_tank, BTL_POS_GROUND_B, 80),
    OVL_ACTOR_NAMED_BY_IDX("general_guy", light_bulb, BTL_POS_AIR_D, 90),
};

static BattleList Formations = {
    BATTLE(Formation_01, "omo_07", "General Guy"),
    {},
};

static StageList Stages = {
    STAGE("omo_07", "omo_07"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
