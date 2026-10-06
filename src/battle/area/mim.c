#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("forest_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("piranha_plant", BTL_POS_GROUND_C, 8),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "mim_01", "Forest Fuzzy x2"),
    BATTLE(Formation_01, "mim_01", "Forest Fuzzy x3"),
    BATTLE(Formation_02, "mim_01", "Forest Fuzzy x4"),
    BATTLE(Formation_03, "mim_01", "Forest Fuzzy, Piranha Plant"),
    BATTLE(Formation_04, "mim_01", "Forest Fuzzy x2, Piranha Plant"),
    BATTLE(Formation_05, "mim_01", "Forest Fuzzy x2, Piranha Plant x2"),
    BATTLE(Formation_06, "mim_01", "Forest Fuzzy x3, Piranha Plant"),
    BATTLE(Formation_07, "mim_01", "Forest Fuzzy, Piranha Plant, Forest Fuzzy, Piranha Plant"),
    BATTLE(Formation_08, "mim_01", "Piranha Plant"),
    BATTLE(Formation_09, "mim_01", "Piranha Plant x2"),
    BATTLE(Formation_0A, "mim_01", "Piranha Plant x3"),
    BATTLE(Formation_0B, "mim_01", "Piranha Plant x4"),
    BATTLE(Formation_0C, "mim_01", "Piranha Plant, Forest Fuzzy"),
    BATTLE(Formation_0D, "mim_01", "Piranha Plant x2, Forest Fuzzy"),
    BATTLE(Formation_0E, "mim_01", "Piranha Plant, Forest Fuzzy x2"),
    BATTLE(Formation_0F, "mim_01", "Piranha Plant, Forest Fuzzy, Piranha Plant"),
    BATTLE(Formation_10, "mim_01", "Bzzap! x2"),
    BATTLE(Formation_11, "mim_01", "Bzzap! x3"),
    {},
};

static StageList Stages = {
    STAGE("mim_01", "mim_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
