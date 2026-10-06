#include "battle/battle.h"

static Formation goomba_1 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
};

static Formation goomba_2 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation goomba_3 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
};

static Formation goomba_1_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation goomba_4 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_D, 7),
};

static Formation goomba_1_spiked_goomba_1 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation goomba_1_paragoomba_1_goomba_1_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_D, 7),
};

static Formation paragoomba_1 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
};

static Formation paragoomba_2 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation paragoomba_3 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

static Formation spiked_goomba_1 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
};

static Formation spiked_goomba_1_goomba_1 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static BattleList Formations = {
    BATTLE(goomba_1, "kmr_04"),
    BATTLE(goomba_2, "kmr_04"),
    BATTLE(goomba_3, "kmr_04"),
    BATTLE(goomba_1_paragoomba_1, "kmr_04"),
    BATTLE(goomba_4, "kmr_04"),
    BATTLE(goomba_1_spiked_goomba_1, "kmr_04"),
    BATTLE(goomba_1_paragoomba_1_goomba_1_paragoomba_1, "kmr_04"),
    BATTLE(paragoomba_1, "kmr_04"),
    BATTLE(paragoomba_2, "kmr_04"),
    BATTLE(paragoomba_3, "kmr_04"),
    BATTLE(spiked_goomba_1, "kmr_04"),
    BATTLE(spiked_goomba_1_goomba_1, "kmr_04"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
