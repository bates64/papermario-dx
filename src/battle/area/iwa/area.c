#include "area.h"

extern ActorBlueprint A(buzzar);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 8),
};

Vec3i A(BossPos) = { 90, 70, 0 };

Formation A(Formation_0C) = {
    ACTOR_BY_POS(A(buzzar), A(BossPos), 10),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("whacka", BTL_POS_GROUND_C, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "iwa_01", "シンエモン"),
    BATTLE(A(Formation_01), "iwa_01", "シンエモンx２"),
    BATTLE(A(Formation_02), "iwa_01", "シンエモンx３"),
    BATTLE(A(Formation_03), "iwa_01", "シンエモン,チョロプー"),
    BATTLE(A(Formation_04), "iwa_01", "シンエモン,チョロプーx２"),
    BATTLE(A(Formation_05), "iwa_01", "チョロプー"),
    BATTLE(A(Formation_06), "iwa_01", "チョロプーx２"),
    BATTLE(A(Formation_07), "iwa_01", "チョロプーx３"),
    BATTLE(A(Formation_08), "iwa_01", "チョロプーx４"),
    BATTLE(A(Formation_09), "iwa_01", "チョロプー,シンエモン"),
    BATTLE(A(Formation_0A), "iwa_01", "チョロプーx２,シンエモン"),
    BATTLE(A(Formation_0B), "iwa_01", "チョロプー,シンエモン,チョロプー"),
    BATTLE(A(Formation_0C), "iwa_02", "ゲーハー"),
    BATTLE(A(Formation_0D), "iwa_02", "コブロン"),
    {},
};

StageList A(Stages) = {
    STAGE("iwa_01", "iwa_01"),
    STAGE("iwa_01b", "iwa_01b"),
    STAGE("iwa_02", "iwa_02"),
    {},
};
