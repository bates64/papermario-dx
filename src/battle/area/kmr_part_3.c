#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("tutorial_spiked_goomba", BTL_POS_GROUND_C, 0),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("tutorial_paragoomba", BTL_POS_AIR_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("egg_jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("para_jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("spiked_para_jr_troopa", BTL_POS_GROUND_B, 0),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("mage_jr_troopa", BTL_POS_GROUND_C, 0),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("final_jr_troopa", BTL_POS_GROUND_C, 0),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kmr_03", "Spiked Goomba (Tutorial)"),
    BATTLE(Formation_01, "kmr_03", "Paragoomba (Tutorial)"),
    BATTLE(Formation_02, "kmr_05b", "Jr. Troopa 1"),
    BATTLE(Formation_03, "nok_01", "Jr. Troopa 2"),
    BATTLE(Formation_04, "mim_01", "Jr. Troopa 4"),
    BATTLE(Formation_05, "mac_01", "Jr. Troopa 5"),
    BATTLE(Formation_06, "sam_01", "Jr. Troopa 6"),
    BATTLE(Formation_07, "kpa_13", "Jr. Troopa 7"),
    {},
};

static StageList Stages = {
    STAGE("kmr_02", "kmr_02"),
    STAGE("kmr_03", "kmr_03"),
    STAGE("kmr_04", "kmr_04"),
    STAGE("kmr_05", "kmr_05b"),
    STAGE("kmr_06", "kmr_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
