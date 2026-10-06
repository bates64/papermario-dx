#include "battle/battle.h"

static Formation forest_fuzzy_2 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation forest_fuzzy_3 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation forest_fuzzy_4 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation forest_fuzzy_1_piranha_plant_1 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 9),
};

static Formation forest_fuzzy_2_piranha_plant_1 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

static Formation forest_fuzzy_2_piranha_plant_2 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation forest_fuzzy_3_piranha_plant_1 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation forest_fuzzy_1_mixed_07 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation piranha_plant_1 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
};

static Formation piranha_plant_2 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 9),
};

static Formation piranha_plant_3 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

static Formation piranha_plant_4 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation piranha_plant_1_forest_fuzzy_1 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation piranha_plant_2_forest_fuzzy_1 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation piranha_plant_1_forest_fuzzy_2 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation piranha_plant_1_forest_fuzzy_1_piranha_plant_1 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

static Formation bzzap_2 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

static Formation bzzap_3 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static BattleList Formations = {
    BATTLE(forest_fuzzy_2, "mim_01"),
    BATTLE(forest_fuzzy_3, "mim_01"),
    BATTLE(forest_fuzzy_4, "mim_01"),
    BATTLE(forest_fuzzy_1_piranha_plant_1, "mim_01"),
    BATTLE(forest_fuzzy_2_piranha_plant_1, "mim_01"),
    BATTLE(forest_fuzzy_2_piranha_plant_2, "mim_01"),
    BATTLE(forest_fuzzy_3_piranha_plant_1, "mim_01"),
    BATTLE(forest_fuzzy_1_mixed_07, "mim_01"),
    BATTLE(piranha_plant_1, "mim_01"),
    BATTLE(piranha_plant_2, "mim_01"),
    BATTLE(piranha_plant_3, "mim_01"),
    BATTLE(piranha_plant_4, "mim_01"),
    BATTLE(piranha_plant_1_forest_fuzzy_1, "mim_01"),
    BATTLE(piranha_plant_2_forest_fuzzy_1, "mim_01"),
    BATTLE(piranha_plant_1_forest_fuzzy_2, "mim_01"),
    BATTLE(piranha_plant_1_forest_fuzzy_1_piranha_plant_1, "mim_01"),
    BATTLE(bzzap_2, "mim_01"),
    BATTLE(bzzap_3, "mim_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
