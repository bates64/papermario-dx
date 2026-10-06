#include "battle/battle.h"


static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_D, 7),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("red_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("white_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 9),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kzn_01", "Lava Bubble x2"),
    BATTLE(Formation_01, "kzn_01", "Lava Bubble x3"),
    BATTLE(Formation_02, "kzn_01", "Lava Bubble x4"),
    BATTLE(Formation_03, "kzn_01", "Lava Bubble, Spike Top x3"),
    BATTLE(Formation_04, "kzn_01", "Lava Bubble x2, Medi Guy"),
    BATTLE(Formation_05, "kzn_01", "Lava Bubble x2, Red Magikoopa"),
    BATTLE(Formation_06, "kzn_01", "Lava Bubble x2, White Magikoopa"),
    BATTLE(Formation_07, "kzn_01", "Lava Bubble x2, Spike Top"),
    BATTLE(Formation_08, "kzn_01", "Spike Top x2"),
    BATTLE(Formation_09, "kzn_01", "Spike Top, Lava Bubble"),
    BATTLE(Formation_0A, "kzn_01", "Spike Top x2, Lava Bubble"),
    BATTLE(Formation_0B, "kzn_01", "Spike Top, Putrid Piranha"),
    BATTLE(Formation_0C, "kzn_01", "Spike Top x2, Putrid Piranha"),
    BATTLE(Formation_0D, "kzn_01", "Spike Top x2, Putrid Piranha x2"),
    BATTLE(Formation_0E, "kzn_01", "Spike Top, Lava Bubble x3"),
    BATTLE(Formation_0F, "kzn_01", "Putrid Piranha x2"),
    BATTLE(Formation_10, "kzn_01", "Putrid Piranha x3"),
    BATTLE(Formation_11, "kzn_01", "Putrid Piranha, Lava Bubble, Putrid Piranha"),
    BATTLE(Formation_12, "kzn_01", "Putrid Piranha x2, Spike Top"),
    BATTLE(Formation_13, "kzn_01", "Putrid Piranha, Spike Top, Putrid Piranha"),
    BATTLE(Formation_14, "kzn_01", "Putrid Piranha, Spike Top, Putrid Piranha, Spike Top"),
    {},
};

static StageList Stages = {
    STAGE("kzn_01", "kzn_01"),
    STAGE("kzn_01b", "kzn_01b"),
    STAGE("kzn_02", "kzn_02"),
    STAGE("kzn_04", "kzn_04"),
    STAGE("kzn_04b", "kzn_04b"),
    STAGE("kzn_04c", "kzn_04c"),
    STAGE("kzn_05", "kzn_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
