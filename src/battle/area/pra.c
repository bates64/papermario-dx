#include "battle/battle.h"


static Vec3i pos_swoopula[] = {
    { 15, 133, -25 },
    { 55, 133, -25 },
    { 95, 133, -25 },
    { 135, 133, -25 },
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[0], 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 9),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 8),
};

static Vec3i pos_swoopula_2[] = {
    { 0, 133, -25 },
    { 40, 133, -25 },
    { 80, 133, -25 },
    { 120, 133, -25 },
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_2[0], 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_2[1], 9),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_2[2], 8),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_2[3], 7),
};

static Vec3i pos_swoopula_3[] = {
    { 0, 133, -25 },
    { 40, 133, -25 },
    { 80, 133, -25 },
};

static Vec3i pos_magikoopa = { 120, 55, 25 };

static Formation Formation_04 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_3[0], 10, 0xFFFFFFFF),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_3[1], 9, 0xFFFFFFFF),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_3[2], 8, 0xFFFFFFFF),
    OVL_ACTOR_NAMED_BY_POS("yellow_magikoopa", flying, pos_magikoopa, 7),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 8),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("yellow_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("green_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("green_magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_NAMED_BY_IDX("white_magikoopa", flying, BTL_POS_AIR_D, 7),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("albino_dino", BTL_POS_GROUND_B, 10)
};

static BattleList Formations = {
    BATTLE(Formation_01, "pra_01", "Swoopula x2"),
    BATTLE(Formation_02, "pra_01", "Swoopula x3"),
    BATTLE(Formation_03, "pra_01", "Swoopula x4"),
    BATTLE(Formation_04, "pra_01", "Swoopula x3, Yellow Magikoopa (Flying)"),
    BATTLE(Formation_05, "pra_01", "White Clubba"),
    BATTLE(Formation_06, "pra_01", "White Clubba x2"),
    BATTLE(Formation_07, "pra_01", "White Clubba x3"),
    BATTLE(Formation_08, "pra_01", "White Clubba x2, Swoopula"),
    BATTLE(Formation_09, "pra_01", "White Clubba x2, Yellow Magikoopa"),
    BATTLE(Formation_0A, "pra_01", "White Clubba x2, White Magikoopa"),
    BATTLE(Formation_0B, "pra_01", "White Clubba x2, White Magikoopa, Red Magikoopa"),
    BATTLE(Formation_0C, "pra_01", "White Clubba, Gray Magikoopa"),
    BATTLE(Formation_0D, "pra_01", "White Clubba x3, Green Magikoopa"),
    BATTLE(Formation_0E, "pra_01", "White Clubba x2, Green Magikoopa, White Magikoopa (Flying)"),
    BATTLE(Formation_0F, "pra_01", "Albino Dino"),
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
