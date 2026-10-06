#include "battle/battle.h"

static Vec3i vector3D_80224070 = { 15, 133, -25 };
static Vec3i vector3D_8022407C = { 55, 133, -25 };
static Vec3i vector3D_80224088 = { 95, 133, -25 };
static Vec3i vector3D_80224094 = { 135, 133, -25 };

static Vec3i vector3D_802240A0 = { 15, 112, -25 };
static Vec3i vector3D_802240AC = { 55, 112, -25 };
static Vec3i vector3D_802240B8 = { 95, 112, -25 };
static Vec3i vector3D_802240C4 = { 135, 112, -25 };

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 8),
};

static Vec3i vector3D_802241E8 = { 80, 133, -25 };
static Vec3i vector3D_802241F4 = { 115, 133, -25 };

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_802241E8, 8),
    OVL_ACTOR_BY_POS("swooper", vector3D_802241F4, 7),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_POS("swooper", vector3D_8022407C, 10),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 9),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_POS("swooper", vector3D_80224070, 10),
    OVL_ACTOR_BY_POS("swooper", vector3D_8022407C, 9),
    OVL_ACTOR_BY_POS("swooper", vector3D_80224088, 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_C, 9),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_C, 8),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("swooper", vector3D_802240B8, 8),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_POS("swooper", vector3D_802240B8, 9),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 10, 1),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 9, 1),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 9, 1),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 8, 1),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240A0, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240B8, 8, 1),
};

static Vec3i vector3D_8022460C = { 0, 112, -25 };

static Vec3i vector3D_80224618 = { 40, 112, -25 };

static Vec3i vector3D_80224624 = { 80, 112, -25 };

static Vec3i vector3D_80224630 = { 120, 112, -25 };

static Formation Formation_12 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_8022460C, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_80224618, 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_80224624, 8, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_80224630, 7, 1),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240A0, 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", vector3D_802240AC, 9, 1),
    OVL_ACTOR_BY_POS("swooper", vector3D_802240B8, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "isk_02b", "Pokey Mummy x2"),
    BATTLE(Formation_01, "isk_02b", "Pokey Mummy x3"),
    BATTLE(Formation_02, "isk_04", "Pokey Mummy, Swooper"),
    BATTLE(Formation_03, "isk_04", "Pokey Mummy x2, Swooper"),
    BATTLE(Formation_04, "isk_04", "Pokey Mummy x2, Swooper x2"),
    BATTLE(Formation_05, "isk_04", "Swooper x2"),
    BATTLE(Formation_06, "isk_04", "Swooper x3"),
    BATTLE(Formation_07, "isk_02b", "Stone Chomp x2"),
    BATTLE(Formation_08, "isk_02b", "Stone Chomp x3"),
    BATTLE(Formation_09, "isk_02b", "Buzzy Beetle x2"),
    BATTLE(Formation_0A, "isk_02b", "Buzzy Beetle x4"),
    BATTLE(Formation_0B, "isk_05", "Buzzy Beetle, Buzzy Beetle (Ceiling), Swooper"),
    BATTLE(Formation_0C, "isk_05", "Buzzy Beetle, Swooper"),
    BATTLE(Formation_0D, "isk_05", "Buzzy Beetle (Ceiling), Buzzy Beetle"),
    BATTLE(Formation_0E, "isk_05", "Buzzy Beetle, Buzzy Beetle (Ceiling)"),
    BATTLE(Formation_0F, "isk_05", "Buzzy Beetle (Ceiling) x2"),
    BATTLE(Formation_10, "isk_05", "Buzzy Beetle, Buzzy Beetle (Ceiling) x2"),
    BATTLE(Formation_11, "isk_05", "Buzzy Beetle (Ceiling) x3"),
    BATTLE(Formation_12, "isk_05", "Buzzy Beetle (Ceiling) x4"),
    BATTLE(Formation_13, "isk_05", "Buzzy Beetle (Ceiling) x2, Swooper"),
    {},
};

static StageList Stages = {
    STAGE("isk_00", "isk_00"),
    STAGE("isk_01", "isk_01"),
    STAGE("isk_02", "isk_02"),
    STAGE("isk_02b", "isk_02b"),
    STAGE("isk_02c", "isk_02c"),
    STAGE("isk_03", "isk_03"),
    STAGE("isk_03b", "isk_03b"),
    STAGE("isk_04", "isk_04"),
    STAGE("isk_05", "isk_05"),
    STAGE("isk_06", "isk_06"),
    STAGE("isk_06b", "isk_06b"),
    STAGE("isk_07", "isk_07"),
    STAGE("isk_08", "isk_08"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
