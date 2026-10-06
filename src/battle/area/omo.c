#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_C, 9),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_15 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_16 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_17 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

static Formation Formation_18 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_19 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_1A = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_1B = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_1C = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_1D = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_1E = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

static Formation Formation_1F = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_20 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_21 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_22 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_23 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_24 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_25 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_26 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_27 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_28 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_29 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation Formation_2A = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_2B = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_2C = {
    OVL_ACTOR_BY_IDX("anti_guy", BTL_POS_GROUND_B, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "omo_04", "Red Shy Guy x2"),
    BATTLE(Formation_01, "omo_04", "Blue Shy Guy x2"),
    BATTLE(Formation_02, "omo_04", "Yellow Shy Guy x2"),
    BATTLE(Formation_03, "omo_04", "Yellow Shy Guy x3"),
    BATTLE(Formation_04, "omo_04", "Pink Shy Guy x2"),
    BATTLE(Formation_05, "omo_04", "Green Shy Guy x2"),
    BATTLE(Formation_06, "omo_04", "Red Shy Guy, Medi Guy x2"),
    BATTLE(Formation_07, "omo_04", "Blue Shy Guy, Groove Guy, Medi Guy"),
    BATTLE(Formation_08, "omo_04", "Yellow Shy Guy, Spy Guy, Medi Guy"),
    BATTLE(Formation_09, "omo_04", "Yellow Shy Guy, Green Shy Guy, Red Shy Guy, Blue Shy Guy"),
    BATTLE(Formation_0A, "omo_04", "Pink Shy Guy, Pyro Guy, Medi Guy"),
    BATTLE(Formation_0B, "omo_04", "Pink Shy Guy, Groove Guy, Medi Guy x2"),
    BATTLE(Formation_0C, "omo_04", "Green Shy Guy, Sky Guy, Medi Guy"),
    BATTLE(Formation_0D, "omo_04", "Sky Guy x2"),
    BATTLE(Formation_0E, "omo_04", "Sky Guy, Yellow Shy Guy"),
    BATTLE(Formation_0F, "omo_04", "Sky Guy x2, Yellow Shy Guy"),
    BATTLE(Formation_10, "omo_04", "Sky Guy, Medi Guy"),
    BATTLE(Formation_11, "omo_04", "Sky Guy x2, Spy Guy"),
    BATTLE(Formation_12, "omo_04", "Sky Guy, Green Shy Guy, Medi Guy"),
    BATTLE(Formation_13, "omo_04", "Sky Guy, Green Shy Guy, Medi Guy x2"),
    BATTLE(Formation_14, "omo_04", "Sky Guy, Groove Guy, Medi Guy"),
    BATTLE(Formation_15, "omo_04", "Spy Guy x2"),
    BATTLE(Formation_16, "omo_04", "Spy Guy, Pyro Guy"),
    BATTLE(Formation_17, "omo_04", "Spy Guy, Medi Guy"),
    BATTLE(Formation_18, "omo_04", "Spy Guy x2, Medi Guy"),
    BATTLE(Formation_19, "omo_04", "Spy Guy x3, Medi Guy"),
    BATTLE(Formation_1A, "omo_04", "Spy Guy x4"),
    BATTLE(Formation_1B, "omo_04", "Spy Guy, Pyro Guy, Groove Guy, Medi Guy"),
    BATTLE(Formation_1C, "omo_04", "Pyro Guy x2"),
    BATTLE(Formation_1D, "omo_04", "Pyro Guy x3"),
    BATTLE(Formation_1E, "omo_04", "Pyro Guy, Medi Guy"),
    BATTLE(Formation_1F, "omo_04", "Pyro Guy x2, Medi Guy"),
    BATTLE(Formation_20, "omo_04", "Pyro Guy x2, Medi Guy x2"),
    BATTLE(Formation_21, "omo_04", "Pyro Guy, Groove Guy, Pyro Guy"),
    BATTLE(Formation_22, "omo_04", "Pyro Guy, Spy Guy, Groove Guy"),
    BATTLE(Formation_23, "omo_04", "Pyro Guy, Groove Guy, Medi Guy x2"),
    BATTLE(Formation_24, "omo_04", "Pyro Guy x2, Spy Guy"),
    BATTLE(Formation_25, "omo_04", "Groove Guy x2"),
    BATTLE(Formation_26, "omo_04", "Groove Guy x3"),
    BATTLE(Formation_27, "omo_04", "Groove Guy, Medi Guy x2"),
    BATTLE(Formation_28, "omo_04", "Groove Guy x2, Medi Guy"),
    BATTLE(Formation_29, "omo_04", "Groove Guy x2, Medi Guy x2"),
    BATTLE(Formation_2A, "omo_04", "Groove Guy x2, Pyro Guy"),
    BATTLE(Formation_2B, "omo_04", "Groove Guy, Blue Shy Guy, Sky Guy"),
    BATTLE(Formation_2C, "omo_04", "Anti Guy"),
    {},
};

static StageList Stages = {
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

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
