#include "area.h"

extern ActorBlueprint A(blooper);
extern ActorBlueprint A(electro_blooper);
extern ActorBlueprint A(super_blooper);

Vec3i A(BlooperPos) = { 80, 45, -10 };

Formation A(Formation_00) = {
    ACTOR_BY_POS(A(blooper), A(BlooperPos), 10),
};

Formation A(Formation_01) = {
    ACTOR_BY_POS(A(electro_blooper), A(BlooperPos), 10),
};

Formation A(Formation_02) = {
    ACTOR_BY_POS(A(super_blooper), A(BlooperPos), 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "tik_01", "ゲッソー"),
    BATTLE(A(Formation_01), "tik_01", "ビリビリゲッソー"),
    BATTLE(A(Formation_02), "tik_01", "ビッグゲッソー　チビゲッソー"),
    {},
};

StageList A(Stages) = {
    STAGE("tik_01", "tik_01"),
    STAGE("tik_02", "tik_02"),
    STAGE("tik_03", "tik_03"),
    STAGE("tik_04", "tik_04"),
    STAGE("tik_05", "tik_05"),
    {},
};
