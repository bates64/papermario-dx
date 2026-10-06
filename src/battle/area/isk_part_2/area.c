#include "area.h"

extern ActorBlueprint A(tutankoopa);

Vec3i A(BossPos) = { 97, 70, 17 };

Formation A(Formation_00) = {
    ACTOR_BY_POS(A(tutankoopa), A(BossPos), 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "isk_01", "カーメン　ワンワン"),
    {},
};

StageList A(Stages) = {
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
