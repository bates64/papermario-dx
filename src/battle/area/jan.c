#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 10, 0),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 9, 1),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 9, 1),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_C, 10),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 9, 1),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 8),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_00, "jan_01", "Spear Guy x2"),
    BATTLE(Formation_01, "jan_01", "Spear Guy x3"),
    BATTLE(Formation_02, "jan_01", "Spear Guy, Jungle Fuzzy"),
    BATTLE(Formation_03, "jan_01", "Spear Guy, Jungle Fuzzy x3"),
    BATTLE(Formation_04, "jan_01", "Spear Guy, Jungle Fuzzy x2"),
    BATTLE(Formation_05, "jan_01", "Spear Guy, Jungle Fuzzy, Spear Guy"),
    BATTLE(Formation_06, "jan_01", "Spear Guy, Jungle Fuzzy, Spear Guy, Jungle Fuzzy"),
    BATTLE(Formation_07, "jan_01", "Spear Guy, Medi Guy, Spike Top"),
    BATTLE(Formation_08, "jan_01", "Hurt Plant x2"),
    BATTLE(Formation_09, "jan_01", "Hurt Plant x3"),
    BATTLE(Formation_0A, "jan_01", "Jungle Fuzzy x2"),
    BATTLE(Formation_0B, "jan_01", "Jungle Fuzzy x3"),
    BATTLE(Formation_0C, "jan_01", "Jungle Fuzzy x4"),
    BATTLE(Formation_0D, "jan_01", "Jungle Fuzzy, Spear Guy, Jungle Fuzzy"),
    BATTLE(Formation_0E, "jan_01", "M. Bush x2"),
    BATTLE(Formation_0F, "jan_01", "M. Bush x3"),
    BATTLE(Formation_10, "jan_01", "M. Bush x4"),
    {},
};

static StageList Stages = {
    STAGE("jan_00", "jan_00"),
    STAGE("jan_01", "jan_01"),
    STAGE("jan_01b", "jan_01b"),
    STAGE("jan_02", "jan_02"),
    STAGE("jan_03", "jan_03"),
    STAGE("jan_03b", "jan_03b"),
    STAGE("jan_04", "jan_04"),
    STAGE("jan_04b", "jan_04b"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
