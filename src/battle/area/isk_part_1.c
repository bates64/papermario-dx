#include "battle/battle.h"

static Vec3i vector3D_80224070 = { 15, 133, -25 };
static Vec3i vector3D_8022407C = { 55, 133, -25 };
static Vec3i vector3D_80224088 = { 95, 133, -25 };
static Vec3i vector3D_80224094 = { 135, 133, -25 };

static Vec3i vector3D_802240A0 = { 15, 112, -25 };
static Vec3i vector3D_802240AC = { 55, 112, -25 };
static Vec3i vector3D_802240B8 = { 95, 112, -25 };
static Vec3i vector3D_802240C4 = { 135, 112, -25 };

static Formation pokey_mummy_2 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_C, 9),
};

static Formation pokey_mummy_3 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_C, 8),
};

static Formation pokey_mummy_1_swooper_1 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 8),
};

static Formation pokey_mummy_2_swooper_1 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 8),
};

static Vec3i vector3D_802241E8 = { 80, 133, -25 };
static Vec3i vector3D_802241F4 = { 115, 133, -25 };

static Formation pokey_mummy_2_swooper_2 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_802241E8, 8),
    OVL_ACTOR_BY_POS("swooper", vector3D_802241F4, 7),
};

static Formation swooper_2 = {
    OVL_ACTOR_BY_POS("swooper", vector3D_8022407C, 10),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 9),
};

static Formation swooper_3 = {
    OVL_ACTOR_BY_POS("swooper", vector3D_80224070, 10),
    OVL_ACTOR_BY_POS("swooper", vector3D_8022407C, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 8),
};

static Formation stone_chomp_2 = {
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_C, 9),
};

static Formation stone_chomp_3 = {
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_C, 8),
};

static Formation buzzy_beetle_2 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 9),
};

static Formation buzzy_beetle_4 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

static Formation buzzy_beetle_1_buzzy_beetle_ceiling_1_swooper_1 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("swooper", vector3D_802240B8, 8),
};

static Formation buzzy_beetle_1_swooper_1 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_POS("swooper", vector3D_802240B8, 9),
};

static Formation buzzy_beetle_ceiling_1_buzzy_beetle_1 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 10, 1),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 9),
};

static Formation buzzy_beetle_1_buzzy_beetle_ceiling_1 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 9, 1),
};

static Formation buzzy_beetle_ceiling_2 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 9, 1),
};

static Formation buzzy_beetle_1_buzzy_beetle_ceiling_2 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 8, 1),
};

static Formation buzzy_beetle_ceiling_3 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240A0, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 8, 1),
};

static Vec3i vector3D_8022460C = { 0, 112, -25 };

static Vec3i vector3D_80224618 = { 40, 112, -25 };

static Vec3i vector3D_80224624 = { 80, 112, -25 };

static Vec3i vector3D_80224630 = { 120, 112, -25 };

static Formation buzzy_beetle_ceiling_4 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_8022460C, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_80224618, 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_80224624, 8, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_80224630, 7, 1),
};

static Formation buzzy_beetle_ceiling_2_swooper_1 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240A0, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("swooper", vector3D_802240B8, 8),
};

static BattleList Formations = {
    BATTLE(pokey_mummy_2, "isk_02b"),
    BATTLE(pokey_mummy_3, "isk_02b"),
    BATTLE(pokey_mummy_1_swooper_1, "isk_04"),
    BATTLE(pokey_mummy_2_swooper_1, "isk_04"),
    BATTLE(pokey_mummy_2_swooper_2, "isk_04"),
    BATTLE(swooper_2, "isk_04"),
    BATTLE(swooper_3, "isk_04"),
    BATTLE(stone_chomp_2, "isk_02b"),
    BATTLE(stone_chomp_3, "isk_02b"),
    BATTLE(buzzy_beetle_2, "isk_02b"),
    BATTLE(buzzy_beetle_4, "isk_02b"),
    BATTLE(buzzy_beetle_1_buzzy_beetle_ceiling_1_swooper_1, "isk_05"),
    BATTLE(buzzy_beetle_1_swooper_1, "isk_05"),
    BATTLE(buzzy_beetle_ceiling_1_buzzy_beetle_1, "isk_05"),
    BATTLE(buzzy_beetle_1_buzzy_beetle_ceiling_1, "isk_05"),
    BATTLE(buzzy_beetle_ceiling_2, "isk_05"),
    BATTLE(buzzy_beetle_1_buzzy_beetle_ceiling_2, "isk_05"),
    BATTLE(buzzy_beetle_ceiling_3, "isk_05"),
    BATTLE(buzzy_beetle_ceiling_4, "isk_05"),
    BATTLE(buzzy_beetle_ceiling_2_swooper_1, "isk_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
