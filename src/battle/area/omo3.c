#include "battle/battle.h"

static Vec3i big_lantern_ghost_pos = { 30, 0, 10 };

static Formation big_lantern_ghost = {
    OVL_ACTOR_BY_POS("big_lantern_ghost", big_lantern_ghost_pos, 10),
};

static Formation goomba_1 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
};

static Formation goomba_2 = {
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("goomba", BTL_POS_GROUND_C, 9),
};

static Formation clubba_2 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 9),
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

static Formation hammer_bro_2 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation hammer_bro_1 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
};

static Formation pokey_2 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10, 0, true),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_C,  9, 0, true),
};

static Formation koopatrol_2 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

static Formation shy_guy_1 = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 10),
};

static BattleList Formations = {
    BATTLE(big_lantern_ghost, "omo_03"),
    BATTLE(goomba_1, "omo_04"),
    BATTLE(goomba_2, "omo_04"),
    BATTLE(clubba_2, "omo_04"),
    BATTLE(fuzzy_2, "omo_04"),
    BATTLE(fuzzy_4, "omo_04"),
    BATTLE(hammer_bro_2, "omo_04"),
    BATTLE(hammer_bro_1, "omo_04"),
    BATTLE(pokey_2, "omo_04"),
    BATTLE(koopatrol_2, "omo_04"),
    BATTLE(shy_guy_1, "omo_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
