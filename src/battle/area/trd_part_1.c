#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 9),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 8),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_15 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_16 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Vec3i BlasterPos1 = { 50, 0, -20 };
static Vec3i BlasterPos2 = { 80, 0, 0 };
static Vec3i BlasterPos3 = { 110, 0, 20 };

static Formation Formation_17 = {
    OVL_ACTOR_BY_POS("bill_blaster", BlasterPos1, 10),
    OVL_ACTOR_BY_POS("bill_blaster", BlasterPos2, 9),
    OVL_ACTOR_BY_POS("bill_blaster", BlasterPos3, 9),
};

static Formation Formation_18 = {
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_C, 9),
};

static Formation Formation_19 = {
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_B, 10),
};

static Formation Formation_1A = {
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "trd_01", "Koopa Troopa"),
    BATTLE(Formation_01, "trd_01", "Koopa Troopa x2"),
    BATTLE(Formation_02, "trd_01", "Koopa Troopa x3"),
    BATTLE(Formation_03, "trd_01", "Koopa Troopa, Bob-omb"),
    BATTLE(Formation_04, "trd_01", "Koopa Troopa, Bob-omb x2"),
    BATTLE(Formation_05, "trd_01", "Koopa Troopa, Bob-omb x3"),
    BATTLE(Formation_06, "trd_01", "Koopa Troopa x2, Bob-omb"),
    BATTLE(Formation_07, "trd_01", "Koopa Troopa x2, Bob-omb x2"),
    BATTLE(Formation_08, "trd_01", "Paratroopa x2"),
    BATTLE(Formation_09, "trd_01", "Paratroopa x3"),
    BATTLE(Formation_0A, "trd_01", "Paratroopa, Koopa Troopa"),
    BATTLE(Formation_0B, "trd_01", "Paratroopa, Koopa Troopa, Paratroopa"),
    BATTLE(Formation_0C, "trd_01", "Paratroopa, Koopa Troopa, Paratroopa, Koopa Troopa"),
    BATTLE(Formation_0D, "trd_01", "Paratroopa, Bob-omb x2"),
    BATTLE(Formation_0E, "trd_01", "Paratroopa, Bob-omb x3"),
    BATTLE(Formation_0F, "trd_01", "Bob-omb"),
    BATTLE(Formation_10, "trd_01", "Bob-omb x2"),
    BATTLE(Formation_11, "trd_01", "Bob-omb x3"),
    BATTLE(Formation_12, "trd_01", "Bob-omb x4"),
    BATTLE(Formation_13, "trd_01", "Bob-omb, Koopa Troopa"),
    BATTLE(Formation_14, "trd_01", "Bob-omb x2, Koopa Troopa"),
    BATTLE(Formation_15, "trd_01", "Bob-omb, Koopa Troopa x2"),
    BATTLE(Formation_16, "trd_01", "Koopa Troopa, Bob-omb x2"),
    BATTLE(Formation_17, "trd_01", "Bill Blaster x3"),
    BATTLE(Formation_18, "trd_01", "Bullet Bill x2"),
    BATTLE(Formation_19, "trd_01", "Bullet Bill"),
    BATTLE(Formation_1A, "trd_01", "Bullet Bill x3"),
    {},
};

static StageList Stages = {
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
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
