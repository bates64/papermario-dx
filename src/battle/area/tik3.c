#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_B, 10),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_A, 10),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_B, 9),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_B, 10),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_C, 9),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_A, 10),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_B, 9),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "tik_01", "Swooper x2"),
    BATTLE(Formation_01, "tik_01", "Swooper x3"),
    BATTLE(Formation_02, "tik_01", "Swoopula x2"),
    BATTLE(Formation_03, "tik_01", "Swoopula x3"),
    {},
};

static StageList Stages = {
    STAGE("tik_01", "tik_01"),
    STAGE("tik_02", "tik_02"),
    STAGE("tik_03", "tik_03"),
    STAGE("tik_04", "tik_04"),
    STAGE("tik_05", "tik_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
