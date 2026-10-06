#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_D, 7),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_D, 7),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 9),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_D, 7),
};

static Formation Formation_15 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 10),
};

static Formation Formation_16 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_17 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_18 = {
    OVL_ACTOR_BY_IDX("kent_c_koopa", BTL_POS_GROUND_B, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "nok_02", "Goomba x2"),
    BATTLE(Formation_01, "nok_02", "Goomba, Spiked Goomba"),
    BATTLE(Formation_02, "nok_02", "Paragoomba x2"),
    BATTLE(Formation_03, "nok_02", "Spiked Goomba, Paragoomba"),
    BATTLE(Formation_04, "nok_02", "Spiked Goomba x2"),
    BATTLE(Formation_05, "nok_02", "Spiked Goomba, Goomba x2"),
    BATTLE(Formation_06, "nok_02", "Spiked Goomba x3"),
    BATTLE(Formation_07, "nok_02", "Spiked Goomba x4"),
    BATTLE(Formation_08, "nok_02", "Koopa Troopa, Goomba"),
    BATTLE(Formation_09, "nok_02", "Koopa Troopa x2"),
    BATTLE(Formation_0A, "nok_02", "Koopa Troopa x3"),
    BATTLE(Formation_0B, "nok_02", "Koopa Troopa, Spiked Goomba"),
    BATTLE(Formation_0C, "nok_02", "Koopa Troopa x2, Spiked Goomba"),
    BATTLE(Formation_0D, "nok_02", "Koopa Troopa, Spiked Goomba x2"),
    BATTLE(Formation_0E, "nok_02", "Koopa Troopa, Paragoomba x2"),
    BATTLE(Formation_0F, "nok_02", "Koopa Troopa, Spiked Goomba, Paragoomba"),
    BATTLE(Formation_10, "nok_02", "Koopa Troopa x2, Spiked Goomba, Paragoomba"),
    BATTLE(Formation_11, "nok_02", "Paratroopa x2"),
    BATTLE(Formation_12, "nok_02", "Paratroopa, Koopa Troopa"),
    BATTLE(Formation_13, "nok_02", "Paratroopa, Koopa Troopa, Spiked Goomba"),
    BATTLE(Formation_14, "nok_02", "Paratroopa, Koopa Troopa, Spiked Goomba x2"),
    BATTLE(Formation_15, "nok_02", "Fuzzy"),
    BATTLE(Formation_16, "nok_02", "Fuzzy x2"),
    BATTLE(Formation_17, "nok_02", "Fuzzy x4"),
    BATTLE(Formation_18, "nok_02", "Kent C. Koopa"),
    {},
};

static StageList Stages = {
    STAGE("nok_01", "nok_01"),
    STAGE("nok_02", "nok_02"),
    STAGE("nok_03", "nok_03"),
    STAGE("nok_04", "nok_04"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
