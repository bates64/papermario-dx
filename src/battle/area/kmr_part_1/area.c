#include "area.h"

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_D, 7),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "kmr_04", "クリボー"),
    BATTLE(A(Formation_01), "kmr_04", "クリボーx２"),
    BATTLE(A(Formation_02), "kmr_04", "クリボーx３"),
    BATTLE(A(Formation_03), "kmr_04", "クリボー、パタクリボー"),
    BATTLE(A(Formation_04), "kmr_04", "クリボーx４"),
    BATTLE(A(Formation_05), "kmr_04", "クリボー,トゲクリボー"),
    BATTLE(A(Formation_06), "kmr_04", "クリボー,パタクリボー,クリボー,パタクリボー"),
    BATTLE(A(Formation_07), "kmr_04", "パタクリボー"),
    BATTLE(A(Formation_08), "kmr_04", "パタクリボーx２"),
    BATTLE(A(Formation_09), "kmr_04", "パタクリボーx３"),
    BATTLE(A(Formation_0A), "kmr_04", "トゲクリボー"),
    BATTLE(A(Formation_0B), "kmr_04", "トゲクリボー、クリボー"),
    {},
};

StageList A(Stages) = {
    STAGE("kmr_02", "kmr_02"),
    STAGE("kmr_03", "kmr_03"),
    STAGE("kmr_04", "kmr_04"),
    STAGE("kmr_05", "kmr_05"),
    STAGE("kmr_06", "kmr_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
