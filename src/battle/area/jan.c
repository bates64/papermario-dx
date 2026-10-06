#include "battle/battle.h"

static Formation spear_guy_2 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 10, 0),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 9, 1),
};

static Formation spear_guy_3 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 9, 1),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
};

static Formation spear_guy_1_jungle_fuzzy_1 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation spear_guy_1_jungle_fuzzy_3 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation spear_guy_1_jungle_fuzzy_2 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation spear_guy_1_jungle_fuzzy_1_spear_guy_1 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
};

static Formation spear_guy_1_jungle_fuzzy_1_spear_guy_1_jungle_fuzzy_1 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation spear_guy_1_medi_guy_1_spike_top_1 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation hurt_plant_2 = {
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_C, 10),
};

static Formation hurt_plant_3 = {
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_C, 8),
};

static Formation jungle_fuzzy_2 = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation jungle_fuzzy_3 = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation jungle_fuzzy_4 = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation jungle_fuzzy_1_spear_guy_1_jungle_fuzzy_1 = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 9, 1),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation m_bush_2 = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 9),
};

static Formation m_bush_3 = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 8),
};

static Formation m_bush_4 = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(spear_guy_2, "jan_01"),
    BATTLE(spear_guy_3, "jan_01"),
    BATTLE(spear_guy_1_jungle_fuzzy_1, "jan_01"),
    BATTLE(spear_guy_1_jungle_fuzzy_3, "jan_01"),
    BATTLE(spear_guy_1_jungle_fuzzy_2, "jan_01"),
    BATTLE(spear_guy_1_jungle_fuzzy_1_spear_guy_1, "jan_01"),
    BATTLE(spear_guy_1_jungle_fuzzy_1_spear_guy_1_jungle_fuzzy_1, "jan_01"),
    BATTLE(spear_guy_1_medi_guy_1_spike_top_1, "jan_01"),
    BATTLE(hurt_plant_2, "jan_01"),
    BATTLE(hurt_plant_3, "jan_01"),
    BATTLE(jungle_fuzzy_2, "jan_01"),
    BATTLE(jungle_fuzzy_3, "jan_01"),
    BATTLE(jungle_fuzzy_4, "jan_01"),
    BATTLE(jungle_fuzzy_1_spear_guy_1_jungle_fuzzy_1, "jan_01"),
    BATTLE(m_bush_2, "jan_01"),
    BATTLE(m_bush_3, "jan_01"),
    BATTLE(m_bush_4, "jan_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
