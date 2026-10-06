#include "area.h"

extern ActorBlueprint A(white_magikoopa);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(white_magikoopa), BTL_POS_GROUND_D, 7),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "jan_01", "ポイズンパックン"),
    BATTLE(A(Formation_01), "jan_01", "ポイズンパックンx２"),
    BATTLE(A(Formation_02), "jan_01", "ポイズンパックンx３"),
    BATTLE(A(Formation_03), "jan_01", "ポイズンパックンx３,ホワイトカメック"),
    {},
};

StageList A(Stages) = {
    STAGE("jan_00", "jan_00"),
    STAGE("jan_01", "jan_01"),
    STAGE("jan_01b", "jan_01b"),
    STAGE("jan_02", "jan_02"),
    STAGE("jan_03", "jan_03"),
    STAGE("jan_03b", "jan_03b"),
    STAGE("jan_04", "jan_04"),
    STAGE("jan_04b", "jan_04b"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
