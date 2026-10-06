#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_NAMED_BY_IDX("anti_guy", trio, BTL_POS_GROUND_A, 10),
    OVL_ACTOR_NAMED_BY_IDX("anti_guy", trio, BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("anti_guy", trio, BTL_POS_GROUND_C, 8),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kpa_01", "Anti Guy x3"),
    BATTLE(Formation_01, "kpa_01", "Duplighost x2"),
    BATTLE(Formation_02, "kpa_01", "Duplighost x4"),
    {},
};

static StageList Stages = {
    STAGE("kpa_01", "kpa_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
