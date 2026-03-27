#include "area.h"

extern Stage A(mim_01);

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
    BATTLE(A(Formation_00), A(mim_01), "グリーンチョロボンx2"),
    BATTLE(A(Formation_01), A(mim_01), "グリーンチョロボンx3"),
    BATTLE(A(Formation_02), A(mim_01), "グリーンチョロボンx4"),
    BATTLE(A(Formation_03), A(mim_01), "グリーンチョロボン,パックンフラワー"),
    BATTLE(A(Formation_04), A(mim_01), "グリーンチョロボンx2,パックンフラワー"),
    BATTLE(A(Formation_05), A(mim_01), "グリーンチョロボンx2,パックンフラワーx2"),
    BATTLE(A(Formation_06), A(mim_01), "グリーンチョロボンx3,パックンフラワー"),
    BATTLE(A(Formation_07), A(mim_01), "グリーンチョロボン,パックンフラワー,グリーンチョロボン,パックンフラワー"),
    BATTLE(A(Formation_08), A(mim_01), "パックンフラワー"),
    BATTLE(A(Formation_09), A(mim_01), "パックンフラワーx2"),
    BATTLE(A(Formation_0A), A(mim_01), "パックンフラワーx3"),
    BATTLE(A(Formation_0B), A(mim_01), "パックンフラワーx4"),
    BATTLE(A(Formation_0C), A(mim_01), "パックンフラワー,グリーンチョロボン"),
    BATTLE(A(Formation_0D), A(mim_01), "パックンフラワーx2,グリーンチョロボン"),
    BATTLE(A(Formation_0E), A(mim_01), "パックンフラワー,グリーンチョロボンx2"),
    BATTLE(A(Formation_0F), A(mim_01), "パックンフラワー,グリーンチョロボン,パックンフラワー"),
    BATTLE(A(Formation_10), A(mim_01), "ハッチーx2"),
    BATTLE(A(Formation_11), A(mim_01), "ハッチーx3"),
    {},
};

StageList A(Stages) = {
    STAGE("mim_01", A(mim_01)),
    {},
};
