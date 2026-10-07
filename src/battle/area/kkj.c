#include "battle/battle.h"

static Formation kammy_koopa = {
    OVL_ACTOR_BY_IDX("kammy_koopa", BTL_POS_AIR_C, 10),
};

static BattleList Formations = {
    BATTLE(kammy_koopa, "kkj_02"),
};

OVL_DEF_BATTLE_AREA(Formations);
