#include "battle/battle.h"


static Vec3i KingPos = { 70, 0, 5 };

static Vec3i CrystalBitPos1 = {  10, 35,  -5 };
static Vec3i CrystalBitPos2 = { 112, 52,  -5 };
static Vec3i CrystalBitPos3 = {  42, 85, -10 };

static Formation crystal_king = {
    OVL_ACTOR_BY_POS("crystal_king", KingPos, 10),
    OVL_ACTOR_BY_POS("crystal_bit:cube", CrystalBitPos1, 9),
    OVL_ACTOR_BY_POS("crystal_bit:sphere", CrystalBitPos2, 8),
    OVL_ACTOR_BY_POS("crystal_bit:prism", CrystalBitPos3, 7),
};

static BattleList Formations = {
    BATTLE(crystal_king, "sam_04"),
};

OVL_DEF_BATTLE_AREA(Formations);
