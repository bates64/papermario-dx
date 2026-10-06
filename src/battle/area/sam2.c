#include "battle/battle.h"

static Vec3i MonstarPos = { 75, 16, 5 };

static Formation monstar = {
    OVL_ACTOR_BY_POS("monstar", MonstarPos, 10),
};

static Formation paragoomba_1_gray_magikoopa_1_test = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_C, 9),
};

static BattleList Formations = {
    BATTLE(monstar, "sam_03"),
    BATTLE(paragoomba_1_gray_magikoopa_1_test, "sam_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
