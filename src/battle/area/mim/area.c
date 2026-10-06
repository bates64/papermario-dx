#include "area.h"

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "mim_01", "グリーンチョロボンx2"),
    BATTLE(A(Formation_01), "mim_01", "グリーンチョロボンx3"),
    BATTLE(A(Formation_02), "mim_01", "グリーンチョロボンx4"),
    BATTLE(A(Formation_03), "mim_01", "グリーンチョロボン,パックンフラワー"),
    BATTLE(A(Formation_04), "mim_01", "グリーンチョロボンx2,パックンフラワー"),
    BATTLE(A(Formation_05), "mim_01", "グリーンチョロボンx2,パックンフラワーx2"),
    BATTLE(A(Formation_06), "mim_01", "グリーンチョロボンx3,パックンフラワー"),
    BATTLE(A(Formation_07), "mim_01", "グリーンチョロボン,パックンフラワー,グリーンチョロボン,パックンフラワー"),
    BATTLE(A(Formation_08), "mim_01", "パックンフラワー"),
    BATTLE(A(Formation_09), "mim_01", "パックンフラワーx2"),
    BATTLE(A(Formation_0A), "mim_01", "パックンフラワーx3"),
    BATTLE(A(Formation_0B), "mim_01", "パックンフラワーx4"),
    BATTLE(A(Formation_0C), "mim_01", "パックンフラワー,グリーンチョロボン"),
    BATTLE(A(Formation_0D), "mim_01", "パックンフラワーx2,グリーンチョロボン"),
    BATTLE(A(Formation_0E), "mim_01", "パックンフラワー,グリーンチョロボンx2"),
    BATTLE(A(Formation_0F), "mim_01", "パックンフラワー,グリーンチョロボン,パックンフラワー"),
    BATTLE(A(Formation_10), "mim_01", "ハッチーx2"),
    BATTLE(A(Formation_11), "mim_01", "ハッチーx3"),
    {},
};

StageList A(Stages) = {
    STAGE("mim_01", "mim_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
