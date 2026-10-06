#include "battle/battle.h"

static Formation pokey_1 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
};

static Formation pokey_2 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 9),
};

static Formation pokey_3 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
};

static Formation pokey_4 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 7),
};

static Formation pokey_1_bandit_1 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 9),
};

static Formation pokey_2_bandit_1 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
};

static Formation pokey_2_bandit_2 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_D, 7),
};

static Formation pokey_1_bandit_1_pokey_1 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
};

static Formation pokey_2_bandit_1_pokey_1 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 7),
};

static Formation bandit_1 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 10),
};

static Formation bandit_2 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 9),
};

static Formation bandit_3 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
};

static Formation bandit_4 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_D, 7),
};

static Formation bandit_1_pokey_1 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 9),
};

static Formation bandit_2_pokey_1 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
};

static Formation bandit_2_pokey_2 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 7),
};

static Formation bandit_1_pokey_1_bandit_1 = {
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(pokey_1, "sbk_02"),
    BATTLE(pokey_2, "sbk_02"),
    BATTLE(pokey_3, "sbk_02"),
    BATTLE(pokey_4, "sbk_02"),
    BATTLE(pokey_1_bandit_1, "sbk_02"),
    BATTLE(pokey_2_bandit_1, "sbk_02"),
    BATTLE(pokey_2_bandit_2, "sbk_02"),
    BATTLE(pokey_1_bandit_1_pokey_1, "sbk_02"),
    BATTLE(pokey_2_bandit_1_pokey_1, "sbk_02"),
    BATTLE(bandit_1, "sbk_02"),
    BATTLE(bandit_2, "sbk_02"),
    BATTLE(bandit_3, "sbk_02"),
    BATTLE(bandit_4, "sbk_02"),
    BATTLE(bandit_1_pokey_1, "sbk_02"),
    BATTLE(bandit_2_pokey_1, "sbk_02"),
    BATTLE(bandit_2_pokey_2, "sbk_02"),
    BATTLE(bandit_1_pokey_1_bandit_1, "sbk_02"),
};

OVL_DEF_BATTLE_AREA(Formations);
