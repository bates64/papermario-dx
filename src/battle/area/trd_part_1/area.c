#include "area.h"

extern ActorBlueprint A(bill_blaster);
extern ActorBlueprint A(bullet_bill);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 9),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 8),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_12) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_14) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_15) = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_16) = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

Vec3i A(BlasterPos1) = { 50, 0, -20 };
Vec3i A(BlasterPos2) = { 80, 0, 0 };
Vec3i A(BlasterPos3) = { 110, 0, 20 };

Formation A(Formation_17) = {
    ACTOR_BY_POS(A(bill_blaster), A(BlasterPos1), 10),
    ACTOR_BY_POS(A(bill_blaster), A(BlasterPos2), 9),
    ACTOR_BY_POS(A(bill_blaster), A(BlasterPos3), 9),
};

Formation A(Formation_18) = {
    ACTOR_BY_IDX(A(bullet_bill), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(bullet_bill), BTL_POS_GROUND_C, 9),
};

Formation A(Formation_19) = {
    ACTOR_BY_IDX(A(bullet_bill), BTL_POS_GROUND_B, 10),
};

Formation A(Formation_1A) = {
    ACTOR_BY_IDX(A(bullet_bill), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(bullet_bill), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(bullet_bill), BTL_POS_GROUND_C, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "trd_01", "ノコノコ"),
    BATTLE(A(Formation_01), "trd_01", "ノコノコx2"),
    BATTLE(A(Formation_02), "trd_01", "ノコノコx3"),
    BATTLE(A(Formation_03), "trd_01", "ノコノコ,ボムへい"),
    BATTLE(A(Formation_04), "trd_01", "ノコノコ,ボムへいx2"),
    BATTLE(A(Formation_05), "trd_01", "ノコノコ,ボムへいx3"),
    BATTLE(A(Formation_06), "trd_01", "ノコノコx2,ボムへい"),
    BATTLE(A(Formation_07), "trd_01", "ノコノコx2,ボムへいx2"),
    BATTLE(A(Formation_08), "trd_01", "パタパタx２"),
    BATTLE(A(Formation_09), "trd_01", "パタパタx３"),
    BATTLE(A(Formation_0A), "trd_01", "パタパタ,ノコノコ"),
    BATTLE(A(Formation_0B), "trd_01", "パタパタ,ノコノコ,パタパタ"),
    BATTLE(A(Formation_0C), "trd_01", "パタパタ,ノコノコ,パタパタ,ノコノコ"),
    BATTLE(A(Formation_0D), "trd_01", "パタパタ,ボムヘイx２"),
    BATTLE(A(Formation_0E), "trd_01", "パタパタ,ボムヘイx３"),
    BATTLE(A(Formation_0F), "trd_01", "ボムへい"),
    BATTLE(A(Formation_10), "trd_01", "ボムへいx2"),
    BATTLE(A(Formation_11), "trd_01", "ボムへいx3"),
    BATTLE(A(Formation_12), "trd_01", "ボムへいx4"),
    BATTLE(A(Formation_13), "trd_01", "ボムへい,ノコノコ"),
    BATTLE(A(Formation_14), "trd_01", "ボムへいx2,ノコノコ"),
    BATTLE(A(Formation_15), "trd_01", "ボムへい,ノコノコx2"),
    BATTLE(A(Formation_16), "trd_01", "ノコノコ,ボムへいx2"),
    BATTLE(A(Formation_17), "trd_01", "キラーたいほうx３"),
    BATTLE(A(Formation_18), "trd_01", "キラーx２"),
    BATTLE(A(Formation_19), "trd_01", "キラー"),
    BATTLE(A(Formation_1A), "trd_01", "キラーx３"),
    {},
};

StageList A(Stages) = {
    STAGE("trd_00",  "trd_00"),
    STAGE("trd_01",  "trd_01"),
    STAGE("trd_02",  "trd_02"),
    STAGE("trd_02b", "trd_02b"),
    STAGE("trd_02c", "trd_02c"),
    STAGE("trd_02d", "trd_02d"),
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

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
