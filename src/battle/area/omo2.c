#include "battle/battle.h"

static Formation general_guy = {
    OVL_ACTOR_BY_IDX("general_guy", BTL_POS_GROUND_C, 70),
    OVL_ACTOR_NAMED_BY_IDX("general_guy", toy_tank, BTL_POS_GROUND_B, 80),
    OVL_ACTOR_NAMED_BY_IDX("general_guy", light_bulb, BTL_POS_AIR_D, 90),
};

static BattleList Formations = {
    BATTLE(general_guy, "omo_07"),
};

OVL_DEF_BATTLE_AREA(Formations);
