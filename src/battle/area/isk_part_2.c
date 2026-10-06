#include "battle/battle.h"

static Vec3i BossPos = { 97, 70, 17 };

static Formation Formation_00 = {
    OVL_ACTOR_BY_POS("tutankoopa", BossPos, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "isk_01", "Tutankoopa, Chain Chomp"),
    {},
};

static StageList Stages = {
    STAGE("isk_00", "isk_00"),
    STAGE("isk_01", "isk_01"),
    STAGE("isk_02", "isk_02"),
    STAGE("isk_02b", "isk_02b"),
    STAGE("isk_02c", "isk_02c"),
    STAGE("isk_03", "isk_03"),
    STAGE("isk_03b", "isk_03b"),
    STAGE("isk_04", "isk_04"),
    STAGE("isk_05", "isk_05"),
    STAGE("isk_06", "isk_06"),
    STAGE("isk_06b", "isk_06b"),
    STAGE("isk_07", "isk_07"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
