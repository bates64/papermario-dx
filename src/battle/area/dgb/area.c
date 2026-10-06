#include "area.h"

extern ActorBlueprint A(tubba_blubba);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_D, 7),
};

Vec3i A(vector3D_8021B348) = { 75, 0, 10 };

Formation A(Formation_04) = {
    ACTOR_BY_POS(A(tubba_blubba), A(vector3D_8021B348), 10),
};

Formation A(Formation_05) = {
    ACTOR_BY_POS(A(tubba_blubba), A(vector3D_8021B348), 10, 1),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "dgb_01", "ガボンへい"),
    BATTLE(A(Formation_01), "dgb_01", "ガボンへいx２"),
    BATTLE(A(Formation_02), "dgb_01", "ガボンへいx３"),
    BATTLE(A(Formation_03), "dgb_01", "ガボンへいx４"),
    BATTLE(A(Formation_04), "dgb_01", "むてきドガボン"),
    BATTLE(A(Formation_05), "dgb_01", "むてきドガボンせりふなし"),
    {},
};

StageList A(Stages) = {
    STAGE("dgb_01", "dgb_01"),
    STAGE("dgb_02", "dgb_02"),
    STAGE("dgb_03", "dgb_03"),
    STAGE("dgb_04", "dgb_04"),
    STAGE("dgb_05", "dgb_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
