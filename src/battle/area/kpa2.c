#include "battle/battle.h"

static Vec3i bowser_pos = { 80, 0, -10 };

static Formation bowser_unused = {
    OVL_ACTOR_BY_IDX("unused_bowser", BTL_POS_GROUND_C, 10),
};

static Formation bowser_opening = {
    OVL_ACTOR_BY_IDX("intro_bowser", BTL_POS_GROUND_C, 10),
};

static Formation bowser_hallway = {
    OVL_ACTOR_BY_IDX("hallway_bowser", BTL_POS_GROUND_C, 10),
};

static Formation bowser_final_1 = {
    OVL_ACTOR_BY_POS("final_bowser_1", bowser_pos, 10),
};

static Formation bowser_final_2 = {
    OVL_ACTOR_BY_POS("final_bowser_2", bowser_pos, 10),
};

static BattleList Formations = {
    BATTLE(bowser_unused, "kpa_01"),
    BATTLE(bowser_opening, "kkj_01"),
    BATTLE(bowser_hallway, "kkj_01"),
    BATTLE(bowser_final_1, "kkj_02"),
    BATTLE(bowser_final_2, "kkj_02"),
};

OVL_DEF_BATTLE_AREA(Formations);
