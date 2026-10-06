#include "battle/battle.h"

static Vec3i BossPos = { 97, 70, 17 };

static Formation tutankoopa = {
    OVL_ACTOR_BY_POS("tutankoopa", BossPos, 10),
};

static BattleList Formations = {
    BATTLE(tutankoopa, "isk_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
