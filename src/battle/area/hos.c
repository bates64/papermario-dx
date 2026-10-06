#include "battle/battle.h"


static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("goombario_tutor", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa_boss", flying, BTL_POS_AIR_B, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "hos_02", "Goombario (Action Command Tutorial)"),
    BATTLE(Formation_01, "hos_01", "Ember x2"),
    BATTLE(Formation_02, "hos_01", "Ember x3"),
    BATTLE(Formation_03, "hos_02", "Magikoopa (After Action Command Tutorial)"),
    {},
};

static StageList Stages = {
    STAGE("hos_00", "hos_00"),
    STAGE("hos_01", "hos_01"),
    STAGE("hos_02", "hos_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
