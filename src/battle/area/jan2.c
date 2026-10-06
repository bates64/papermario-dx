#include "battle/battle.h"


static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_00, "jan_01", "Putrid Piranha"),
    BATTLE(Formation_01, "jan_01", "Putrid Piranha x2"),
    BATTLE(Formation_02, "jan_01", "Putrid Piranha x3"),
    BATTLE(Formation_03, "jan_01", "Putrid Piranha x3, White Magikoopa"),
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
