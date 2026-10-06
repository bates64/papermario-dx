#include "battle/battle.h"

static Formation chan = {
    OVL_ACTOR_BY_IDX("chan", BTL_POS_GROUND_C, 10),
};

static Formation lee = {
    OVL_ACTOR_BY_IDX("lee", BTL_POS_GROUND_C, 10),
};

static Formation master_1 = {
    OVL_ACTOR_BY_IDX("master1", BTL_POS_GROUND_C, 10),
};

static Formation master_2 = {
    OVL_ACTOR_BY_IDX("master2", BTL_POS_GROUND_C, 10),
};

static Formation master_3 = {
    OVL_ACTOR_BY_IDX("master3", BTL_POS_GROUND_C, 10),
};

static BattleList Formations = {
    BATTLE(chan, "mac_02"),
    BATTLE(lee, "mac_02"),
    BATTLE(master_1, "mac_02"),
    BATTLE(master_2, "mac_02"),
    BATTLE(master_3, "mac_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
