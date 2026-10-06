#include "battle/battle.h"

static Formation red_shy_guy_2 = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation blue_shy_guy_2 = {
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation yellow_shy_guy_2 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation yellow_shy_guy_3 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 8),
};

static Formation pink_shy_guy_2 = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation green_shy_guy_2 = {
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation red_shy_guy_1_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation blue_shy_guy_1_groove_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation yellow_shy_guy_1_spy_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation yellow_shy_guy_1_mixed_09 = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_D, 7),
};

static Formation pink_shy_guy_1_pyro_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation pink_shy_guy_1_groove_guy_1_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation green_shy_guy_1_sky_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation sky_guy_2 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_C, 9),
};

static Formation sky_guy_1_yellow_shy_guy_1 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 9),
};

static Formation sky_guy_2_yellow_shy_guy_1 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 8),
};

static Formation sky_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

static Formation sky_guy_2_spy_guy_1 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
};

static Formation sky_guy_1_green_shy_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation sky_guy_1_green_shy_guy_1_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation sky_guy_1_groove_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation spy_guy_2 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 9),
};

static Formation spy_guy_1_pyro_guy_1 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 9),
};

static Formation spy_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

static Formation spy_guy_2_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation spy_guy_3_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation spy_guy_4 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_D, 7),
};

static Formation spy_guy_1_pyro_guy_1_groove_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation pyro_guy_2 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 9),
};

static Formation pyro_guy_3 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

static Formation pyro_guy_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

static Formation pyro_guy_2_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation pyro_guy_2_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation pyro_guy_1_groove_guy_1_pyro_guy_1 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

static Formation pyro_guy_1_spy_guy_1_groove_guy_1 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 8),
};

static Formation pyro_guy_1_groove_guy_1_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation pyro_guy_2_spy_guy_1 = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
};

static Formation groove_guy_2 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 9),
};

static Formation groove_guy_3 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_C, 8),
};

static Formation groove_guy_1_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation groove_guy_2_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation groove_guy_2_medi_guy_2 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

static Formation groove_guy_2_pyro_guy_1 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

static Formation groove_guy_1_blue_shy_guy_1_sky_guy_1 = {
    OVL_ACTOR_BY_IDX("groove_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_C, 8),
};

static Formation anti_guy = {
    OVL_ACTOR_BY_IDX("anti_guy", BTL_POS_GROUND_B, 10),
};

static BattleList Formations = {
    BATTLE(red_shy_guy_2, "omo_04"),
    BATTLE(blue_shy_guy_2, "omo_04"),
    BATTLE(yellow_shy_guy_2, "omo_04"),
    BATTLE(yellow_shy_guy_3, "omo_04"),
    BATTLE(pink_shy_guy_2, "omo_04"),
    BATTLE(green_shy_guy_2, "omo_04"),
    BATTLE(red_shy_guy_1_medi_guy_2, "omo_04"),
    BATTLE(blue_shy_guy_1_groove_guy_1_medi_guy_1, "omo_04"),
    BATTLE(yellow_shy_guy_1_spy_guy_1_medi_guy_1, "omo_04"),
    BATTLE(yellow_shy_guy_1_mixed_09, "omo_04"),
    BATTLE(pink_shy_guy_1_pyro_guy_1_medi_guy_1, "omo_04"),
    BATTLE(pink_shy_guy_1_groove_guy_1_medi_guy_2, "omo_04"),
    BATTLE(green_shy_guy_1_sky_guy_1_medi_guy_1, "omo_04"),
    BATTLE(sky_guy_2, "omo_04"),
    BATTLE(sky_guy_1_yellow_shy_guy_1, "omo_04"),
    BATTLE(sky_guy_2_yellow_shy_guy_1, "omo_04"),
    BATTLE(sky_guy_1_medi_guy_1, "omo_04"),
    BATTLE(sky_guy_2_spy_guy_1, "omo_04"),
    BATTLE(sky_guy_1_green_shy_guy_1_medi_guy_1, "omo_04"),
    BATTLE(sky_guy_1_green_shy_guy_1_medi_guy_2, "omo_04"),
    BATTLE(sky_guy_1_groove_guy_1_medi_guy_1, "omo_04"),
    BATTLE(spy_guy_2, "omo_04"),
    BATTLE(spy_guy_1_pyro_guy_1, "omo_04"),
    BATTLE(spy_guy_1_medi_guy_1, "omo_04"),
    BATTLE(spy_guy_2_medi_guy_1, "omo_04"),
    BATTLE(spy_guy_3_medi_guy_1, "omo_04"),
    BATTLE(spy_guy_4, "omo_04"),
    BATTLE(spy_guy_1_pyro_guy_1_groove_guy_1_medi_guy_1, "omo_04"),
    BATTLE(pyro_guy_2, "omo_04"),
    BATTLE(pyro_guy_3, "omo_04"),
    BATTLE(pyro_guy_1_medi_guy_1, "omo_04"),
    BATTLE(pyro_guy_2_medi_guy_1, "omo_04"),
    BATTLE(pyro_guy_2_medi_guy_2, "omo_04"),
    BATTLE(pyro_guy_1_groove_guy_1_pyro_guy_1, "omo_04"),
    BATTLE(pyro_guy_1_spy_guy_1_groove_guy_1, "omo_04"),
    BATTLE(pyro_guy_1_groove_guy_1_medi_guy_2, "omo_04"),
    BATTLE(pyro_guy_2_spy_guy_1, "omo_04"),
    BATTLE(groove_guy_2, "omo_04"),
    BATTLE(groove_guy_3, "omo_04"),
    BATTLE(groove_guy_1_medi_guy_2, "omo_04"),
    BATTLE(groove_guy_2_medi_guy_1, "omo_04"),
    BATTLE(groove_guy_2_medi_guy_2, "omo_04"),
    BATTLE(groove_guy_2_pyro_guy_1, "omo_04"),
    BATTLE(groove_guy_1_blue_shy_guy_1_sky_guy_1, "omo_04"),
    BATTLE(anti_guy, "omo_04"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
