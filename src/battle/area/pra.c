#include "battle/battle.h"


static Vec3i pos_swoopula[] = {
    { 15, 133, -25 },
    { 55, 133, -25 },
    { 95, 133, -25 },
    { 135, 133, -25 },
};

static Formation swoopula_2 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 9),
};

static Formation swoopula_3 = {
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

static Formation swoopula_4 = {
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

static Formation swoopula_3_yellow_magikoopa_flying_1 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_3[0], 10, 0xFFFFFFFF),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_3[1], 9, 0xFFFFFFFF),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula_3[2], 8, 0xFFFFFFFF),
    OVL_ACTOR_NAMED_BY_POS("yellow_magikoopa", flying, pos_magikoopa, 7),
};

static Formation white_clubba_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
};

static Formation white_clubba_2 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 9),
};

static Formation white_clubba_3 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
};

static Formation white_clubba_2_swoopula_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 8),
};

static Formation white_clubba_2_yellow_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("yellow_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation white_clubba_2_white_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation white_clubba_2_white_magikoopa_1_red_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation white_clubba_1_gray_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation white_clubba_3_green_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("green_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation white_clubba_2_mixed_0d = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("green_magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_NAMED_BY_IDX("white_magikoopa", flying, BTL_POS_AIR_D, 7),
};

static Formation albino_dino_1 = {
    OVL_ACTOR_BY_IDX("albino_dino", BTL_POS_GROUND_B, 10)
};

static BattleList Formations = {
    BATTLE(swoopula_2, "pra_01"),
    BATTLE(swoopula_3, "pra_01"),
    BATTLE(swoopula_4, "pra_01"),
    BATTLE(swoopula_3_yellow_magikoopa_flying_1, "pra_01"),
    BATTLE(white_clubba_1, "pra_01"),
    BATTLE(white_clubba_2, "pra_01"),
    BATTLE(white_clubba_3, "pra_01"),
    BATTLE(white_clubba_2_swoopula_1, "pra_01"),
    BATTLE(white_clubba_2_yellow_magikoopa_1, "pra_01"),
    BATTLE(white_clubba_2_white_magikoopa_1, "pra_01"),
    BATTLE(white_clubba_2_white_magikoopa_1_red_magikoopa_1, "pra_01"),
    BATTLE(white_clubba_1_gray_magikoopa_1, "pra_01"),
    BATTLE(white_clubba_3_green_magikoopa_1, "pra_01"),
    BATTLE(white_clubba_2_mixed_0d, "pra_01"),
    BATTLE(albino_dino_1, "pra_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
