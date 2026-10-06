#include "battle/battle.h"


static Formation action_command_tutorial = {
    OVL_ACTOR_BY_IDX("goombario_tutor", BTL_POS_GROUND_B, 10),
};

static Formation ember_2 = {
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 9),
};

static Formation ember_3 = {
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 8),
};

static Formation magikoopa_miniboss = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa_boss", flying, BTL_POS_AIR_B, 10),
};

static BattleList Formations = {
    BATTLE(action_command_tutorial, "hos_02"),
    BATTLE(ember_2, "hos_01"),
    BATTLE(ember_3, "hos_01"),
    BATTLE(magikoopa_miniboss, "hos_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
