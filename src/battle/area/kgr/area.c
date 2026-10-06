#include "area.h"

extern ActorBlueprint A(fuzzipede);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(fuzzipede), BTL_POS_GROUND_C, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "kgr_01", "ケムシ"),
    {},
};

StageList A(Stages) = {
    STAGE("kgr_01", "kgr_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
