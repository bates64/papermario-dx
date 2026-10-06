#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("chan", BTL_POS_GROUND_C, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("lee", BTL_POS_GROUND_C, 10),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("master1", BTL_POS_GROUND_C, 10),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("master2", BTL_POS_GROUND_C, 10),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("master3", BTL_POS_GROUND_C, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "mac_02", "Chan"),
    BATTLE(Formation_01, "mac_02", "Lee"),
    BATTLE(Formation_02, "mac_02", "The Master Round 1"),
    BATTLE(Formation_03, "mac_02", "The Master Round 2"),
    BATTLE(Formation_04, "mac_02", "The Master Round 3"),
    {},
};

static StageList Stages = {
    STAGE("mac_01", "mac_01"),
    STAGE("mac_02", "mac_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
