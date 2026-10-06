#include "battle/battle.h"

static Vec3i huff_n_puff_pos = { 80, 80, 0 };

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("huff_n_puff", huff_n_puff_pos, 10),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 10),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("spike", BTL_POS_AIR_B, 10),
};

static BattleList Formations = {
    BATTLE(Formation_01, "flo_04", "Huff N. Puff"),
    BATTLE(Formation_02, "flo_01", "Monty Mole (Flower Fields)"),
    BATTLE(Formation_03, "flo_01", "Monty Mole (Flower Fields) x2"),
    BATTLE(Formation_04, "flo_01", "Monty Mole (Flower Fields) x3"),
    BATTLE(Formation_05, "flo_01", "Monty Mole (Flower Fields) x4"),
    BATTLE(Formation_06, "flo_01", "Spike (Lakilester)"),
    {},
};

static StageList Stages = {
    STAGE("flo_01", "flo_01"),
    STAGE("flo_01b", "flo_01b"),
    STAGE("flo_01c", "flo_01c"),
    STAGE("flo_02", "flo_02"),
    STAGE("flo_02b", "flo_02b"),
    STAGE("flo_02c", "flo_02c"),
    STAGE("flo_03", "flo_03"),
    STAGE("flo_04", "flo_04"),
    STAGE("flo_05", "flo_05"),
    STAGE("flo_06", "flo_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
