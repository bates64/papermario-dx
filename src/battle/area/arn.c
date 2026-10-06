#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 10),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_D, 7),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 10),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 9),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_D, 7),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 10),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_D, 7),
};

static Vec3i vector3D_802280C0 = { 90, 20, 0 };

static Formation Formation_0F = {
    OVL_ACTOR_BY_POS("tubbas_heart", vector3D_802280C0, 10),
};

static Vec3i vector3D_802280E8 = { 75, 0, 10 };

static Formation Formation_10 = {
    OVL_ACTOR_BY_POS("tubba_blubba", vector3D_802280E8, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "arn_01", "Hyper Goomba"),
    BATTLE(Formation_01, "arn_01", "Hyper Goomba x2"),
    BATTLE(Formation_02, "arn_01", "Hyper Goomba x3"),
    BATTLE(Formation_03, "arn_01", "Hyper Goomba x2, Hyper Paragoomba"),
    BATTLE(Formation_04, "arn_01", "Hyper Goomba x3, Hyper Paragoomba"),
    BATTLE(Formation_05, "arn_01", "Hyper Goomba x2, Hyper Paragoomba, Hyper Goomba"),
    BATTLE(Formation_06, "arn_01", "Hyper Paragoomba"),
    BATTLE(Formation_07, "arn_01", "Hyper Paragoomba x2"),
    BATTLE(Formation_08, "arn_01", "Hyper Paragoomba x3"),
    BATTLE(Formation_09, "arn_01", "Hyper Paragoomba x4"),
    BATTLE(Formation_0A, "arn_01", "Hyper Cleft"),
    BATTLE(Formation_0B, "arn_01", "Hyper Cleft x2"),
    BATTLE(Formation_0C, "arn_01", "Hyper Cleft x3"),
    BATTLE(Formation_0D, "arn_01", "Hyper Cleft, Hyper Goomba x2"),
    BATTLE(Formation_0E, "arn_01", "Hyper Cleft x2, Hyper Goomba x2"),
    BATTLE(Formation_0F, "arn_06", "Tubba's Heart"),
    BATTLE(Formation_10, "arn_01", "Tubba Blubba"),
    {},
};

static StageList Stages = {
    STAGE("arn_01", "arn_01"),
    STAGE("arn_02", "arn_02"),
    STAGE("arn_03", "arn_03"),
    STAGE("arn_04", "arn_04"),
    STAGE("arn_05", "arn_05"),
    STAGE("arn_06", "arn_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
