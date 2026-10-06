#include "battle/battle.h"

static Formation clubba_1 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
};

static Formation clubba_2 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 9),
};

static Formation clubba_3 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 8),
};

static Formation clubba_4 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_D, 7),
};

static Vec3i vector3D_8021B348 = { 75, 0, 10 };

static Formation tubba_blubba = {
    OVL_ACTOR_BY_POS("tubba_blubba_dgb", vector3D_8021B348, 10),
};

static Formation tubba_blubba_no_dialogue = {
    OVL_ACTOR_BY_POS("tubba_blubba_dgb", vector3D_8021B348, 10, 1),
};

static BattleList Formations = {
    BATTLE(clubba_1, "dgb_01"),
    BATTLE(clubba_2, "dgb_01"),
    BATTLE(clubba_3, "dgb_01"),
    BATTLE(clubba_4, "dgb_01"),
    BATTLE(tubba_blubba, "dgb_01"),
    BATTLE(tubba_blubba_no_dialogue, "dgb_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
