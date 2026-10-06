#include "area.h"

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_B, 10),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_A, 10),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_B, 9),
    OVL_ACTOR_BY_IDX("swooper", BTL_POS_TOP_C, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_B, 10),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_C, 9),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_A, 10),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_B, 9),
    OVL_ACTOR_BY_IDX("swoopula", BTL_POS_TOP_C, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "tik_01", "バサバサx２"),
    BATTLE(A(Formation_01), "tik_01", "バサバサx３"),
    BATTLE(A(Formation_02), "tik_01", "バサバサチュルルx２"),
    BATTLE(A(Formation_03), "tik_01", "バサバサチュルルx３"),
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
