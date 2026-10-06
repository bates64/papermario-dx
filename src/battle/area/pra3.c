#include "battle/battle.h"

static Vec3i pos_swoopula[] = {
    { 15, 133, -25 },
    { 55, 133, -25 },
    { 95, 133, -25 },
    { 135, 133, -25 },
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[0], 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_01, "pra_01", "Swoopula x2, Duplighost"),
    BATTLE(Formation_02, "pra_01", "Duplighost"),
    BATTLE(Formation_03, "pra_01", "Duplighost x2"),
    BATTLE(Formation_04, "pra_01", "Duplighost x3"),
    BATTLE(Formation_05, "pra_01", "Duplighost x4"),
    BATTLE(Formation_06, "pra_01", "Duplighost x2, Swoopula"),
    BATTLE(Formation_07, "pra_01", "Duplighost, Swoopula, Duplighost"),
    BATTLE(Formation_08, "pra_01", "Duplighost, Red Magikoopa"),
    BATTLE(Formation_09, "pra_01", "Duplighost x2, Red Magikoopa"),
    BATTLE(Formation_0A, "pra_01", "Duplighost, White Clubba, Duplighost"),
    BATTLE(Formation_0B, "pra_01", "Duplighost x2, Gray Magikoopa, Red Magikoopa"),
    BATTLE(Formation_0C, "pra_01", "White Clubba x2, Duplighost"),
    {},
};

static StageList Stages = {
    STAGE("pra_01", "pra_01"),
    STAGE("pra_02", "pra_02"),
    STAGE("pra_03", "pra_03"),
    STAGE("pra_03b", "pra_03b"),
    STAGE("pra_03c", "pra_03c"),
    STAGE("pra_04", "pra_04"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
