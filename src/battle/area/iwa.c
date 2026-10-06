#include "battle/battle.h"

static Formation cleft_1 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
};

static Formation cleft_2 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 9),
};

static Formation cleft_3 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 8),
};

static Formation cleft_1_monty_mole_1 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
};

static Formation cleft_1_monty_mole_2 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

static Formation monty_mole_1 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
};

static Formation monty_mole_2 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
};

static Formation monty_mole_3 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

static Formation monty_mole_4 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_D, 7),
};

static Formation monty_mole_1_cleft_1 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 9),
};

static Formation monty_mole_2_cleft_1 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 8),
};

static Formation monty_mole_1_cleft_1_monty_mole_1 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

static Vec3i BossPos = { 90, 70, 0 };

static Formation buzzar = {
    OVL_ACTOR_BY_POS("buzzar", BossPos, 10),
};

static Formation whacka = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("whacka", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(cleft_1, "iwa_01"),
    BATTLE(cleft_2, "iwa_01"),
    BATTLE(cleft_3, "iwa_01"),
    BATTLE(cleft_1_monty_mole_1, "iwa_01"),
    BATTLE(cleft_1_monty_mole_2, "iwa_01"),
    BATTLE(monty_mole_1, "iwa_01"),
    BATTLE(monty_mole_2, "iwa_01"),
    BATTLE(monty_mole_3, "iwa_01"),
    BATTLE(monty_mole_4, "iwa_01"),
    BATTLE(monty_mole_1_cleft_1, "iwa_01"),
    BATTLE(monty_mole_2_cleft_1, "iwa_01"),
    BATTLE(monty_mole_1_cleft_1_monty_mole_1, "iwa_01"),
    BATTLE(buzzar, "iwa_02"),
    BATTLE(whacka, "iwa_02"),
};

OVL_DEF_BATTLE_AREA(Formations);
