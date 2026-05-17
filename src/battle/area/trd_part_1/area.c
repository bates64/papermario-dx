#include "area.h"

extern ActorBlueprint A(bill_blaster);
extern ActorBlueprint A(bullet_bill);

extern Stage A(trd_00);
extern Stage A(trd_01);
extern Stage A(trd_02);
extern Stage A(trd_02b);
extern Stage A(trd_02c);
extern Stage A(trd_02d);
extern Stage A(trd_03);
extern Stage A(trd_04);
extern Stage A(trd_05);
extern Stage A(trd_05b);
extern Stage A(trd_05c);
extern Stage A(trd_05d);
extern Stage A(trd_05e);
extern Stage A(trd_05f);

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
    BATTLE(A(Formation_00), A(trd_01), "ノコノコ"),
    BATTLE(A(Formation_01), A(trd_01), "ノコノコx2"),
    BATTLE(A(Formation_02), A(trd_01), "ノコノコx3"),
    BATTLE(A(Formation_03), A(trd_01), "ノコノコ,ボムへい"),
    BATTLE(A(Formation_04), A(trd_01), "ノコノコ,ボムへいx2"),
    BATTLE(A(Formation_05), A(trd_01), "ノコノコ,ボムへいx3"),
    BATTLE(A(Formation_06), A(trd_01), "ノコノコx2,ボムへい"),
    BATTLE(A(Formation_07), A(trd_01), "ノコノコx2,ボムへいx2"),
    BATTLE(A(Formation_08), A(trd_01), "パタパタx２"),
    BATTLE(A(Formation_09), A(trd_01), "パタパタx３"),
    BATTLE(A(Formation_0A), A(trd_01), "パタパタ,ノコノコ"),
    BATTLE(A(Formation_0B), A(trd_01), "パタパタ,ノコノコ,パタパタ"),
    BATTLE(A(Formation_0C), A(trd_01), "パタパタ,ノコノコ,パタパタ,ノコノコ"),
    BATTLE(A(Formation_0D), A(trd_01), "パタパタ,ボムヘイx２"),
    BATTLE(A(Formation_0E), A(trd_01), "パタパタ,ボムヘイx３"),
    BATTLE(A(Formation_0F), A(trd_01), "ボムへい"),
    BATTLE(A(Formation_10), A(trd_01), "ボムへいx2"),
    BATTLE(A(Formation_11), A(trd_01), "ボムへいx3"),
    BATTLE(A(Formation_12), A(trd_01), "ボムへいx4"),
    BATTLE(A(Formation_13), A(trd_01), "ボムへい,ノコノコ"),
    BATTLE(A(Formation_14), A(trd_01), "ボムへいx2,ノコノコ"),
    BATTLE(A(Formation_15), A(trd_01), "ボムへい,ノコノコx2"),
    BATTLE(A(Formation_16), A(trd_01), "ノコノコ,ボムへいx2"),
    BATTLE(A(Formation_17), A(trd_01), "キラーたいほうx３"),
    BATTLE(A(Formation_18), A(trd_01), "キラーx２"),
    BATTLE(A(Formation_19), A(trd_01), "キラー"),
    BATTLE(A(Formation_1A), A(trd_01), "キラーx３"),
    {},
};

StageList A(Stages) = {
    STAGE("trd_00",  A(trd_00)),
    STAGE("trd_01",  A(trd_01)),
    STAGE("trd_02",  A(trd_02)),
    STAGE("trd_02b", A(trd_02b)),
    STAGE("trd_02c", A(trd_02c)),
    STAGE("trd_02d", A(trd_02d)),
    STAGE("trd_03",  A(trd_03)),
    STAGE("trd_04",  A(trd_04)),
    STAGE("trd_05",  A(trd_05)),
    STAGE("trd_05b", A(trd_05b)),
    STAGE("trd_05c", A(trd_05c)),
    STAGE("trd_05d", A(trd_05d)),
    STAGE("trd_05e", A(trd_05e)),
    STAGE("trd_05f", A(trd_05f)),
    {},
};
