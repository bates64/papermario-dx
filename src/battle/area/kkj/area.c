#include "area.h"

extern ActorBlueprint A(kammy_koopa);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(kammy_koopa), BTL_POS_AIR_C, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "kkj_02", "カメックばば（ピーチ、ティンクせん）"),
    {},
};

StageList A(Stages) = {
    STAGE("kpa_05", "kkj_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
