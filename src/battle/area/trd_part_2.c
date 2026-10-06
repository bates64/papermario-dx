#include "battle/battle.h"

static Formation koopa_bros = {
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", green, BTL_POS_GROUND_A, 10),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", yellow, BTL_POS_GROUND_A, 9),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", black, BTL_POS_GROUND_A, 8),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", red, BTL_POS_GROUND_A, 7),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", fake_bowser, BTL_POS_GROUND_D, 6),
};

static BattleList Formations = {
    BATTLE(koopa_bros, "trd_00"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
