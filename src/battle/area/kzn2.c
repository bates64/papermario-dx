#include "battle/battle.h"

static Vec3i lava_piranha_pos = { 60, 60, 0 };

static Formation lava_piranha = {
    OVL_ACTOR_BY_POS("lava_piranha", lava_piranha_pos, 60),
};

static Vec3i petit_piranha_pos1 = { 40, 60, 0 };
static Vec3i petit_piranha_pos2 = { 80, 60, 0 };

static Formation petit_piranha = {
    OVL_ACTOR_BY_POS("petit_piranha", petit_piranha_pos1, 10),
    OVL_ACTOR_BY_POS("petit_piranha", petit_piranha_pos2, 10),
};

static BattleList Formations = {
    BATTLE(lava_piranha, "kzn_05"),
    BATTLE(petit_piranha, "kzn_05"),
};

OVL_DEF_BATTLE_AREA(Formations);
