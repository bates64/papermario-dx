#include "battle/battle.h"

static Formation hyper_goomba_1 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 10),
};

static Formation hyper_goomba_2 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 9),
};

static Formation hyper_goomba_3 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
};

static Formation hyper_goomba_2_hyper_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
};

static Formation hyper_goomba_3_hyper_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_D, 7),
};

static Formation hyper_goomba_2_hyper_paragoomba_1_hyper_goomba_1 = {
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_D, 7),
};

static Formation hyper_paragoomba_1 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 10),
};

static Formation hyper_paragoomba_2 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 9),
};

static Formation hyper_paragoomba_3 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
};

static Formation hyper_paragoomba_4 = {
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("hyper_paragoomba", BTL_POS_AIR_D, 7),
};

static Formation hyper_cleft_1 = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 10),
};

static Formation hyper_cleft_2 = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_C, 9),
};

static Formation hyper_cleft_3 = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_C, 8),
};

static Formation hyper_cleft_1_hyper_goomba_2 = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
};

static Formation hyper_cleft_2_hyper_goomba_2 = {
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hyper_cleft", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hyper_goomba", BTL_POS_GROUND_D, 7),
};

static Vec3i vector3D_802280C0 = { 90, 20, 0 };

static Formation tubbas_heart = {
    OVL_ACTOR_BY_POS("tubbas_heart", vector3D_802280C0, 10),
};

static Vec3i vector3D_802280E8 = { 75, 0, 10 };

static Formation tubba_blubba = {
    OVL_ACTOR_BY_POS("tubba_blubba", vector3D_802280E8, 10),
};

static BattleList Formations = {
    BATTLE(hyper_goomba_1, "arn_01"),
    BATTLE(hyper_goomba_2, "arn_01"),
    BATTLE(hyper_goomba_3, "arn_01"),
    BATTLE(hyper_goomba_2_hyper_paragoomba_1, "arn_01"),
    BATTLE(hyper_goomba_3_hyper_paragoomba_1, "arn_01"),
    BATTLE(hyper_goomba_2_hyper_paragoomba_1_hyper_goomba_1, "arn_01"),
    BATTLE(hyper_paragoomba_1, "arn_01"),
    BATTLE(hyper_paragoomba_2, "arn_01"),
    BATTLE(hyper_paragoomba_3, "arn_01"),
    BATTLE(hyper_paragoomba_4, "arn_01"),
    BATTLE(hyper_cleft_1, "arn_01"),
    BATTLE(hyper_cleft_2, "arn_01"),
    BATTLE(hyper_cleft_3, "arn_01"),
    BATTLE(hyper_cleft_1_hyper_goomba_2, "arn_01"),
    BATTLE(hyper_cleft_2_hyper_goomba_2, "arn_01"),
    BATTLE(tubbas_heart, "arn_06"),
    BATTLE(tubba_blubba, "arn_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
