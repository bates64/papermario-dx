#include "battle/battle.h"

static Vec3i bowser_pos = { 80, 0, -10 };

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("unused_bowser", BTL_POS_GROUND_C, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("intro_bowser", BTL_POS_GROUND_C, 10),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("hallway_bowser", BTL_POS_GROUND_C, 10),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_POS("final_bowser_1", bowser_pos, 10),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_POS("final_bowser_2", bowser_pos, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kpa_01", "Bowser"),
    BATTLE(Formation_01, "kkj_01", "Bowser (Opening)"),
    BATTLE(Formation_02, "kkj_01", "Bowser (Final Battle 1)"),
    BATTLE(Formation_03, "kkj_02", "Bowser (Final Battle 2)"),
    BATTLE(Formation_04, "kkj_02", "Bowser (Final Battle 3)"),
    {},
};

static StageList Stages = {
    STAGE("kpa_01", "kpa_01"),
    STAGE("kpa_02", "kkj_01"),
    STAGE("kpa_03", "kkj_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
