#include "battle/battle.h"


static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_C, 8),
};

static Vec3i blaster_pos_1 = { 70, 0, -20 };

static Vec3i blaster_pos_2 = { 100, 0, 0 };

static Formation Formation_02 = {
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_1, 10),
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_2, 9),
};

static Vec3i pos_3 = { 130, 0, 25 };

static Formation Formation_03 = {
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_1, 10),
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_2, 9),
    OVL_ACTOR_BY_POS("koopatrol", pos_3, 8),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_1, 10),
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_2, 9),
    OVL_ACTOR_BY_POS("magikoopa", pos_3, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kpa_01", "Bombshell Bill x2"),
    BATTLE(Formation_01, "kpa_01", "Bombshell Bill x3"),
    BATTLE(Formation_02, "kpa_01", "Bombshell Blaster x2"),
    BATTLE(Formation_03, "kpa_01", "Bombshell Blaster x2, Koopatrol"),
    BATTLE(Formation_04, "kpa_01", "Bombshell Blaster x2, Magikoopa"),
    {},
};

static StageList Stages = {
    STAGE("kpa_01", "kpa_01"),
    STAGE("kpa_01b", "kpa_01b"),
    STAGE("kpa_02", "kpa_02"),
    STAGE("kpa_03", "kpa_03"),
    STAGE("kpa_04", "kpa_04"),
    STAGE("kpa_04b", "kpa_04b"),
    STAGE("kpa_04c", "kpa_04c"),
    STAGE("kpa_05", "kpa_05"),
    STAGE("kpa_07", "kpa_07"),
    STAGE("kpa_08", "kpa_08"),
    STAGE("kpa_09", "kpa_09"),
    STAGE("kpa_11", "kpa_11"),
    STAGE("kpa_13", "kpa_13"),
    STAGE("kpa_14", "kpa_14"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
