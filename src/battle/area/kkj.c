#include "battle/battle.h"

static Formation kammy_koopa = {
    OVL_ACTOR_BY_IDX("kammy_koopa", BTL_POS_AIR_C, 10),
};

static BattleList Formations = {
    BATTLE(kammy_koopa, "kkj_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
