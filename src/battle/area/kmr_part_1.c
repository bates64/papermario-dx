#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_D, 7),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_D, 7),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kmr_04", "Goomba"),
    BATTLE(Formation_01, "kmr_04", "Goomba x2"),
    BATTLE(Formation_02, "kmr_04", "Goomba x3"),
    BATTLE(Formation_03, "kmr_04", "Goomba, Paragoomba"),
    BATTLE(Formation_04, "kmr_04", "Goomba x4"),
    BATTLE(Formation_05, "kmr_04", "Goomba, Spiked Goomba"),
    BATTLE(Formation_06, "kmr_04", "Goomba, Paragoomba, Goomba, Paragoomba"),
    BATTLE(Formation_07, "kmr_04", "Paragoomba"),
    BATTLE(Formation_08, "kmr_04", "Paragoomba x2"),
    BATTLE(Formation_09, "kmr_04", "Paragoomba x3"),
    BATTLE(Formation_0A, "kmr_04", "Spiked Goomba"),
    BATTLE(Formation_0B, "kmr_04", "Spiked Goomba, Goomba"),
    {},
};

static StageList Stages = {
    STAGE("kmr_02", "kmr_02"),
    STAGE("kmr_03", "kmr_03"),
    STAGE("kmr_04", "kmr_04"),
    STAGE("kmr_05", "kmr_05"),
    STAGE("kmr_06", "kmr_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
