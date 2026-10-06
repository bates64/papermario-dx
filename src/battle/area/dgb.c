#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("clubba", BTL_POS_GROUND_D, 7),
};

static Vec3i vector3D_8021B348 = { 75, 0, 10 };

static Formation Formation_04 = {
    OVL_ACTOR_BY_POS("tubba_blubba_dgb", vector3D_8021B348, 10),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_POS("tubba_blubba_dgb", vector3D_8021B348, 10, 1),
};

static BattleList Formations = {
    BATTLE(Formation_00, "dgb_01", "Clubba"),
    BATTLE(Formation_01, "dgb_01", "Clubba x2"),
    BATTLE(Formation_02, "dgb_01", "Clubba x3"),
    BATTLE(Formation_03, "dgb_01", "Clubba x4"),
    BATTLE(Formation_04, "dgb_01", "Invincible Tubba Blubba"),
    BATTLE(Formation_05, "dgb_01", "Invincible Tubba Blubba (No Dialogue)"),
    {},
};

static StageList Stages = {
    STAGE("dgb_01", "dgb_01"),
    STAGE("dgb_02", "dgb_02"),
    STAGE("dgb_03", "dgb_03"),
    STAGE("dgb_04", "dgb_04"),
    STAGE("dgb_05", "dgb_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
