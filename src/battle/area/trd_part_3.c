#include "battle/battle.h"

static Formation star_spirit_tutorial = {
    OVL_ACTOR_BY_IDX("eldstar", BTL_POS_AIR_C, 10),
};

static BattleList Formations = {
    BATTLE(star_spirit_tutorial, "nok_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
