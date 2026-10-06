#include "area.h"

extern ActorBlueprint A(chan);
extern ActorBlueprint A(lee);
extern ActorBlueprint A(master1);
extern ActorBlueprint A(master2);
extern ActorBlueprint A(master3);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(chan), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_01) = {
    ACTOR_BY_IDX(A(lee), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_02) = {
    ACTOR_BY_IDX(A(master1), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_03) = {
    ACTOR_BY_IDX(A(master2), BTL_POS_GROUND_C, 10),
};

Formation A(Formation_04) = {
    ACTOR_BY_IDX(A(master3), BTL_POS_GROUND_C, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "mac_02", "チェン"),
    BATTLE(A(Formation_01), "mac_02", "リー"),
    BATTLE(A(Formation_02), "mac_02", "シショー その１"),
    BATTLE(A(Formation_03), "mac_02", "シショー その２"),
    BATTLE(A(Formation_04), "mac_02", "シショー その３"),
    {},
};

StageList A(Stages) = {
    STAGE("mac_01", "mac_01"),
    STAGE("mac_02", "mac_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
