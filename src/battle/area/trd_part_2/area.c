#include "area.h"

extern ActorBlueprint A(green_ninja_koopa);
extern ActorBlueprint A(yellow_ninja_koopa);
extern ActorBlueprint A(black_ninja_koopa);
extern ActorBlueprint A(red_ninja_koopa);
extern ActorBlueprint A(fake_bowser);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(green_ninja_koopa), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(yellow_ninja_koopa), BTL_POS_GROUND_A, 9),
    ACTOR_BY_IDX(A(black_ninja_koopa), BTL_POS_GROUND_A, 8),
    ACTOR_BY_IDX(A(red_ninja_koopa), BTL_POS_GROUND_A, 7),
    ACTOR_BY_IDX(A(fake_bowser), BTL_POS_GROUND_D, 6),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "trd_00", "ノコブロス"),
    {},
};

StageList A(Stages) = {
    STAGE("trd_00",  "trd_00"),
    STAGE("trd_01",  "trd_01"),
    STAGE("trd_02",  "trd_02"),
    STAGE("trd_02b", "trd_02b"),
    STAGE("trd_03",  "trd_03"),
    STAGE("trd_04",  "trd_04"),
    STAGE("trd_05",  "trd_05"),
    STAGE("trd_05b", "trd_05b"),
    STAGE("trd_05c", "trd_05c"),
    STAGE("trd_05d", "trd_05d"),
    STAGE("trd_05e", "trd_05e"),
    STAGE("trd_05f", "trd_05f"),
    {},
};
