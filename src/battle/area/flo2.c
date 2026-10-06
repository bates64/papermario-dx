#include "battle/battle.h"

static Vec3i huff_n_puff_pos = { 80, 80, 0 };

static Formation huff_n_puff = {
    OVL_ACTOR_BY_POS("huff_n_puff", huff_n_puff_pos, 10),
};

static Formation monty_mole_1 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 10),
};

static Formation monty_mole_2 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_C, 9),
};

static Formation monty_mole_3 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_C, 8),
};

static Formation monty_mole_4 = {
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("monty_mole_boss", BTL_POS_GROUND_D, 7),
};

static Formation lakilester = {
    OVL_ACTOR_BY_IDX("spike", BTL_POS_AIR_B, 10),
};

static BattleList Formations = {
    BATTLE(huff_n_puff, "flo_04"),
    BATTLE(monty_mole_1, "flo_01"),
    BATTLE(monty_mole_2, "flo_01"),
    BATTLE(monty_mole_3, "flo_01"),
    BATTLE(monty_mole_4, "flo_01"),
    BATTLE(lakilester, "flo_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
