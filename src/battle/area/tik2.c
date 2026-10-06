#include "battle/battle.h"

static Vec3i BlooperPos = { 80, 45, -10 };

static Formation blooper = {
    OVL_ACTOR_BY_POS("blooper", BlooperPos, 10),
};

static Formation electro_blooper = {
    OVL_ACTOR_BY_POS("electro_blooper", BlooperPos, 10),
};

static Formation super_blooper = {
    OVL_ACTOR_BY_POS("super_blooper", BlooperPos, 10),
};

static BattleList Formations = {
    BATTLE(blooper, "tik_01"),
    BATTLE(electro_blooper, "tik_01"),
    BATTLE(super_blooper, "tik_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
