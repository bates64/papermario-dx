#include "battle/battle.h"

static Vec3i big_lantern_ghost_pos = { 30, 0, 10 };

static Formation Formation_00 = {
    OVL_ACTOR_BY_POS("big_lantern_ghost", big_lantern_ghost_pos, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10, 0, true),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C,  9, 0, true),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "omo_03", "Big Lantern Ghost"),
    BATTLE(Formation_01, "omo_04", "Goomba (Peach Interlude)"),
    BATTLE(Formation_02, "omo_04", "Goomba x2 (Peach Interlude)"),
    BATTLE(Formation_03, "omo_04", "Clubba x2 (Peach Interlude)"),
    BATTLE(Formation_04, "omo_04", "Fuzzy x2 (Peach Interlude)"),
    BATTLE(Formation_05, "omo_04", "Fuzzy x4 (Peach Interlude)"),
    BATTLE(Formation_06, "omo_04", "Hammer Bro x2 (Peach Interlude)"),
    BATTLE(Formation_07, "omo_04", "Hammer Bro (Peach Interlude)"),
    BATTLE(Formation_08, "omo_04", "Pokey x2 (Peach Interlude)"),
    BATTLE(Formation_09, "omo_04", "Koopatrol x2 (Peach Interlude)"),
    BATTLE(Formation_0A, "omo_01", "Shy Guy"),
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
