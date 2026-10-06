#include "battle/battle.h"

static Vec3i BlooperPos = { 80, 45, -10 };

static Formation Formation_00 = {
    OVL_ACTOR_BY_POS("blooper", BlooperPos, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("electro_blooper", BlooperPos, 10),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_POS("super_blooper", BlooperPos, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "tik_01", "Blooper"),
    BATTLE(Formation_01, "tik_01", "Electro Blooper"),
    BATTLE(Formation_02, "tik_01", "Super Blooper, Blooper Baby"),
    {},
};

static StageList Stages = {
    STAGE("tik_01", "tik_01"),
    STAGE("tik_02", "tik_02"),
    STAGE("tik_03", "tik_03"),
    STAGE("tik_04", "tik_04"),
    STAGE("tik_05", "tik_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
