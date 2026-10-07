#include "battle/battle.h"


static Formation putrid_piranha_1 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
};

static Formation putrid_piranha_2 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

static Formation putrid_piranha_3 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation putrid_piranha_3_white_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(putrid_piranha_1, "jan_01"),
    BATTLE(putrid_piranha_2, "jan_01"),
    BATTLE(putrid_piranha_3, "jan_01"),
    BATTLE(putrid_piranha_3_white_magikoopa_1, "jan_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
