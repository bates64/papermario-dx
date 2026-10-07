#include "battle/battle.h"

static Formation goomba_2 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation goomba_1_spiked_goomba_1 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation paragoomba_2 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation spiked_goomba_1_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 9),
};

static Formation spiked_goomba_2 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation spiked_goomba_1_goomba_2 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 8),
};

static Formation spiked_goomba_3 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation spiked_goomba_4 = {
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_D, 7),
};

static Formation koopa_troopa_1_goomba_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation koopa_troopa_2 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation koopa_troopa_3 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_1_spiked_goomba_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 9),
};

static Formation koopa_troopa_2_spiked_goomba_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_1_spiked_goomba_2 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_1_paragoomba_2 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

static Formation koopa_troopa_1_spiked_goomba_1_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_C, 8),
};

static Formation koopa_troopa_2_spiked_goomba_1_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_D, 7),
};

static Formation paratroopa_2 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 9),
};

static Formation paratroopa_1_koopa_troopa_1 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation paratroopa_1_koopa_troopa_1_spiked_goomba_1 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
};

static Formation paratroopa_1_koopa_troopa_1_spiked_goomba_2 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiked_goomba", BTL_POS_GROUND_D, 7),
};

static Formation fuzzy_1 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 10),
};

static Formation fuzzy_2 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation fuzzy_4 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation kent_c_koopa = {
    OVL_ACTOR_BY_IDX("kent_c_koopa", BTL_POS_GROUND_B, 10),
};

static BattleList Formations = {
    BATTLE(goomba_2, "nok_02"),
    BATTLE(goomba_1_spiked_goomba_1, "nok_02"),
    BATTLE(paragoomba_2, "nok_02"),
    BATTLE(spiked_goomba_1_paragoomba_1, "nok_02"),
    BATTLE(spiked_goomba_2, "nok_02"),
    BATTLE(spiked_goomba_1_goomba_2, "nok_02"),
    BATTLE(spiked_goomba_3, "nok_02"),
    BATTLE(spiked_goomba_4, "nok_02"),
    BATTLE(koopa_troopa_1_goomba_1, "nok_02"),
    BATTLE(koopa_troopa_2, "nok_02"),
    BATTLE(koopa_troopa_3, "nok_02"),
    BATTLE(koopa_troopa_1_spiked_goomba_1, "nok_02"),
    BATTLE(koopa_troopa_2_spiked_goomba_1, "nok_02"),
    BATTLE(koopa_troopa_1_spiked_goomba_2, "nok_02"),
    BATTLE(koopa_troopa_1_paragoomba_2, "nok_02"),
    BATTLE(koopa_troopa_1_spiked_goomba_1_paragoomba_1, "nok_02"),
    BATTLE(koopa_troopa_2_spiked_goomba_1_paragoomba_1, "nok_02"),
    BATTLE(paratroopa_2, "nok_02"),
    BATTLE(paratroopa_1_koopa_troopa_1, "nok_02"),
    BATTLE(paratroopa_1_koopa_troopa_1_spiked_goomba_1, "nok_02"),
    BATTLE(paratroopa_1_koopa_troopa_1_spiked_goomba_2, "nok_02"),
    BATTLE(fuzzy_1, "nok_02"),
    BATTLE(fuzzy_2, "nok_02"),
    BATTLE(fuzzy_4, "nok_02"),
    BATTLE(kent_c_koopa, "nok_02"),
};

OVL_DEF_BATTLE_AREA(Formations);
