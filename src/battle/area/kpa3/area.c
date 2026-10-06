#include "area.h"

extern ActorBlueprint A(duplighost);
extern ActorBlueprint A(anti_guy);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(anti_guy), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(anti_guy), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(anti_guy), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_01) = {
    ACTOR_BY_IDX(A(duplighost), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(duplighost), BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    ACTOR_BY_IDX(A(duplighost), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(duplighost), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(duplighost), BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(duplighost), BTL_POS_GROUND_D, 7),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "kpa_01", "ブラックヘイホーx３"),
    BATTLE(A(Formation_01), "kpa_01", "バケバケx２"),
    BATTLE(A(Formation_02), "kpa_01", "バケバケx４"),
    {},
};

StageList A(Stages) = {
    STAGE("kpa_01", "kpa_01"),
    {},
};
