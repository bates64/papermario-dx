#include "battle/battle.h"

static Vec3i pos_swoopula[] = {
    { 15, 133, -25 },
    { 55, 133, -25 },
    { 95, 133, -25 },
    { 135, 133, -25 },
};

static Formation swoopula_2_duplighost_1 = {
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[0], 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation duplighost_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
};

static Formation duplighost_2 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 9),
};

static Formation duplighost_3 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation duplighost_4 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_D, 7),
};

static Formation duplighost_2_swoopula_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[2], 8),
};

static Formation duplighost_1_swoopula_1_duplighost_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("swoopula", pos_swoopula[1], 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation duplighost_1_red_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation duplighost_2_red_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation duplighost_1_white_clubba_1_duplighost_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static Formation duplighost_2_gray_magikoopa_1_red_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation white_clubba_2_duplighost_1 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(swoopula_2_duplighost_1, "pra_01"),
    BATTLE(duplighost_1, "pra_01"),
    BATTLE(duplighost_2, "pra_01"),
    BATTLE(duplighost_3, "pra_01"),
    BATTLE(duplighost_4, "pra_01"),
    BATTLE(duplighost_2_swoopula_1, "pra_01"),
    BATTLE(duplighost_1_swoopula_1_duplighost_1, "pra_01"),
    BATTLE(duplighost_1_red_magikoopa_1, "pra_01"),
    BATTLE(duplighost_2_red_magikoopa_1, "pra_01"),
    BATTLE(duplighost_1_white_clubba_1_duplighost_1, "pra_01"),
    BATTLE(duplighost_2_gray_magikoopa_1_red_magikoopa_1, "pra_01"),
    BATTLE(white_clubba_2_duplighost_1, "pra_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
