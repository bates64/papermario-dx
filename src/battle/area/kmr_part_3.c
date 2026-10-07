#include "battle/battle.h"

static Formation spiked_goomba_tutorial = {
    OVL_ACTOR_BY_IDX("tutorial_spiked_goomba", BTL_POS_GROUND_C, 0),
};

static Formation paragoomba_tutorial = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("tutorial_paragoomba", BTL_POS_AIR_C, 9),
};

static Formation jr_troopa_1 = {
    OVL_ACTOR_BY_IDX("jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation jr_troopa_2 = {
    OVL_ACTOR_BY_IDX("egg_jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation jr_troopa_4 = {
    OVL_ACTOR_BY_IDX("para_jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation jr_troopa_5 = {
    OVL_ACTOR_BY_IDX("spiked_para_jr_troopa", BTL_POS_GROUND_B, 0),
};

static Formation jr_troopa_6 = {
    OVL_ACTOR_BY_IDX("mage_jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation jr_troopa_7 = {
    OVL_ACTOR_BY_IDX("final_jr_troopa", BTL_POS_GROUND_C, 0),
};

static BattleList Formations = {
    BATTLE(spiked_goomba_tutorial, "kmr_03"),
    BATTLE(paragoomba_tutorial, "kmr_03"),
    BATTLE(jr_troopa_1, "kmr_05:b"),
    BATTLE(jr_troopa_2, "nok_01"),
    BATTLE(jr_troopa_4, "mim_01"),
    BATTLE(jr_troopa_5, "mac_01"),
    BATTLE(jr_troopa_6, "sam_01"),
    BATTLE(jr_troopa_7, "kpa_13"),
};

OVL_DEF_BATTLE_AREA(Formations);
