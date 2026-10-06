#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 7),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 9),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_D, 7),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 7),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 10),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 7),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "sbk_02", "Pokey"),
    BATTLE(Formation_01, "sbk_02", "Pokey x2"),
    BATTLE(Formation_02, "sbk_02", "Pokey x3"),
    BATTLE(Formation_03, "sbk_02", "Yellow Pokey x4"),
    BATTLE(Formation_04, "sbk_02", "Pokey, Bandit"),
    BATTLE(Formation_05, "sbk_02", "Pokey x2, Bandit"),
    BATTLE(Formation_06, "sbk_02", "Pokey x2, Bandit x2"),
    BATTLE(Formation_07, "sbk_02", "Pokey, Bandit, Pokey"),
    BATTLE(Formation_08, "sbk_02", "Pokey x2, Bandit, Pokey"),
    BATTLE(Formation_09, "sbk_02", "Bandit"),
    BATTLE(Formation_0A, "sbk_02", "Bandit x2"),
    BATTLE(Formation_0B, "sbk_02", "Bandit x3"),
    BATTLE(Formation_0C, "sbk_02", "Bandit x4"),
    BATTLE(Formation_0D, "sbk_02", "Bandit, Pokey"),
    BATTLE(Formation_0E, "sbk_02", "Bandit x2, Pokey"),
    BATTLE(Formation_0F, "sbk_02", "Bandit x2, Pokey x2"),
    BATTLE(Formation_10, "sbk_02", "Bandit, Pokey, Bandit"),
    {},
};

static StageList Stages = {
    STAGE("sbk_01", "sbk_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
