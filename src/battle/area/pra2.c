#include "battle/battle.h"


static Vec3i KingPos = { 70, 0, 5 };

static Vec3i CrystalBitPos1 = {  10, 35,  -5 };
static Vec3i CrystalBitPos2 = { 112, 52,  -5 };
static Vec3i CrystalBitPos3 = {  42, 85, -10 };

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("crystal_king", KingPos, 10),
    OVL_ACTOR_BY_POS("crystal_bit", CrystalBitPos1, 9),
    OVL_ACTOR_NAMED_BY_POS("crystal_bit", sphere, CrystalBitPos2, 8),
    OVL_ACTOR_NAMED_BY_POS("crystal_bit", prism, CrystalBitPos3, 7),
};

static BattleList Formations = {
    BATTLE(Formation_01, "sam_04", "Crystal King"),
    {},
};

static StageList Stages = {
    STAGE("sam_04", "sam_04"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
