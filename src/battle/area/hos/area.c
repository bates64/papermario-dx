#include "area.h"

extern ActorBlueprint A(goombario_tutor);
extern ActorBlueprint A(magikoopa_flying);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(goombario_tutor), BTL_POS_GROUND_B, 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_B, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "hos_02", "クリオ（ＡＣヘルプ）"),
    BATTLE(A(Formation_01), "hos_01", "エルモスx２"),
    BATTLE(A(Formation_02), "hos_01", "エルモスx３"),
    BATTLE(A(Formation_03), "hos_02", "カメック（ＡＣヘルプご）"),
    {},
};

StageList A(Stages) = {
    STAGE("hos_00", "hos_00"),
    STAGE("hos_01", "hos_01"),
    STAGE("hos_02", "hos_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
