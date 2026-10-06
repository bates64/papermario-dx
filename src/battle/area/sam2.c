#include "battle/battle.h"

static Vec3i MonstarPos = { 75, 16, 5 };

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("monstar", MonstarPos, 10),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_C, 9),
};

static BattleList Formations = {
    BATTLE(Formation_01, "sam_03", "Monstar"),
    BATTLE(Formation_02, "sam_01", "Paragoomba, Gray Magikoopa (Test)"),
    {},
};

static StageList Stages = {
    STAGE("sam_01", "sam_01"),
    STAGE("sam_02", "sam_02"),
    STAGE("sam_02b", "sam_02b"),
    STAGE("sam_02c", "sam_02c"),
    STAGE("sam_02d", "sam_02d"),
    STAGE("sam_03", "sam_03"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
