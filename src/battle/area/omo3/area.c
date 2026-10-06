#include "area.h"

extern ActorBlueprint A(big_lantern_ghost);

Vec3i A(big_lantern_ghost_pos) = { 30, 0, 10 };

Formation A(Formation_00) = {
    ACTOR_BY_POS(A(big_lantern_ghost), A(big_lantern_ghost_pos), 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10, 0, true),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C,  9, 0, true),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "omo_03", "ビッグカンテラくん"),
    BATTLE(A(Formation_01), "omo_04", "クリボー（ピーチへん）"),
    BATTLE(A(Formation_02), "omo_04", "クリボーx２（ピーチへん）"),
    BATTLE(A(Formation_03), "omo_04", "ガボンへいx２（ピーチへん）"),
    BATTLE(A(Formation_04), "omo_04", "チョロボンx２（ピーチへん）"),
    BATTLE(A(Formation_05), "omo_04", "チョロボンx４（ピーチへん）"),
    BATTLE(A(Formation_06), "omo_04", "ハンマーブロスx２（ピーチへん）"),
    BATTLE(A(Formation_07), "omo_04", "ハンマーブロス（ピーチへん）"),
    BATTLE(A(Formation_08), "omo_04", "サンボx２（ピーチへん）"),
    BATTLE(A(Formation_09), "omo_04", "トゲノコx２（ピーチへん）"),
    BATTLE(A(Formation_0A), "omo_01", "ヘイホー"),
    {},
};

StageList A(Stages) = {
    STAGE("omo_01", "omo_01"),
    STAGE("omo_02", "omo_02"),
    STAGE("omo_03", "omo_03"),
    STAGE("omo_03b", "omo_03b"),
    STAGE("omo_04", "omo_04"),
    STAGE("omo_05", "omo_05"),
    STAGE("omo_05b", "omo_05b"),
    STAGE("omo_06", "omo_06"),
    STAGE("omo_07", "omo_07"),
    {},
};
