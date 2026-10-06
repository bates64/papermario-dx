#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_D, 7),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

static Vec3i BossPos = { 90, 70, 0 };

static Formation Formation_0C = {
    OVL_ACTOR_BY_POS("buzzar", BossPos, 10),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("whacka", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "iwa_01", "Cleft"),
    BATTLE(Formation_01, "iwa_01", "Cleft x2"),
    BATTLE(Formation_02, "iwa_01", "Cleft x3"),
    BATTLE(Formation_03, "iwa_01", "Cleft, Monty Mole"),
    BATTLE(Formation_04, "iwa_01", "Cleft, Monty Mole x2"),
    BATTLE(Formation_05, "iwa_01", "Monty Mole"),
    BATTLE(Formation_06, "iwa_01", "Monty Mole x2"),
    BATTLE(Formation_07, "iwa_01", "Monty Mole x3"),
    BATTLE(Formation_08, "iwa_01", "Monty Mole x4"),
    BATTLE(Formation_09, "iwa_01", "Monty Mole, Cleft"),
    BATTLE(Formation_0A, "iwa_01", "Monty Mole x2, Cleft"),
    BATTLE(Formation_0B, "iwa_01", "Monty Mole, Cleft, Monty Mole"),
    BATTLE(Formation_0C, "iwa_02", "Buzzar"),
    BATTLE(Formation_0D, "iwa_02", "Whacka"),
    {},
};

static StageList Stages = {
    STAGE("iwa_01", "iwa_01"),
    STAGE("iwa_01b", "iwa_01b"),
    STAGE("iwa_02", "iwa_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
