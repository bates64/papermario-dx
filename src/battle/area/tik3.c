#include "battle/battle.h"

static Formation swooper_2 = {
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_B, 10),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_C, 9),
};

static Formation swooper_3 = {
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_A, 10),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_B, 9),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_C, 8),
};

static Formation swoopula_2 = {
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_B, 10),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_C, 9),
};

static Formation swoopula_3 = {
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_A, 10),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_B, 9),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_C, 8),
};

static BattleList Formations = {
    BATTLE(swooper_2, "tik_01"),
    BATTLE(swooper_3, "tik_01"),
    BATTLE(swoopula_2, "tik_01"),
    BATTLE(swoopula_3, "tik_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
