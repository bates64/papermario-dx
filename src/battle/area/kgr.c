#include "battle/battle.h"

static Formation fuzzipede = {
    OVL_ACTOR_BY_IDX("fuzzipede", BTL_POS_GROUND_C, 10),
};

static BattleList Formations = {
    BATTLE(fuzzipede, "kgr_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
