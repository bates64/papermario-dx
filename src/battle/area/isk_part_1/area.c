#include "area.h"

Vec3i A(vector3D_80224070) = { 15, 133, -25 };
Vec3i A(vector3D_8022407C) = { 55, 133, -25 };
Vec3i A(vector3D_80224088) = { 95, 133, -25 };
Vec3i A(vector3D_80224094) = { 135, 133, -25 };

Vec3i A(vector3D_802240A0) = { 15, 112, -25 };
Vec3i A(vector3D_802240AC) = { 55, 112, -25 };
Vec3i A(vector3D_802240B8) = { 95, 112, -25 };
Vec3i A(vector3D_802240C4) = { 135, 112, -25 };

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_80224088), 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_80224088), 8),
};

Vec3i A(vector3D_802241E8) = { 80, 133, -25 };
Vec3i A(vector3D_802241F4) = { 115, 133, -25 };

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pokey_mummy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_802241E8), 8),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_802241F4), 7),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_POS("swooper", A(vector3D_8022407C), 10),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_80224088), 9),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_POS("swooper", A(vector3D_80224070), 10),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_8022407C), 9),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_80224088), 8),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("stone_chomp", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240AC), 9, 1),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_802240B8), 8),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_802240B8), 9),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240AC), 10, 1),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240B8), 9, 1),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240AC), 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240B8), 9, 1),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240AC), 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240B8), 8, 1),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240A0), 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240AC), 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240B8), 8, 1),
};

Vec3i A(vector3D_8022460C) = { 0, 112, -25 };

Vec3i A(vector3D_80224618) = { 40, 112, -25 };

Vec3i A(vector3D_80224624) = { 80, 112, -25 };

Vec3i A(vector3D_80224630) = { 120, 112, -25 };

Formation A(Formation_12) = {
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_8022460C), 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_80224618), 9, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_80224624), 8, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_80224630), 7, 1),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240A0), 10, 1),
    OVL_ACTOR_BY_POS("buzzy_beetle", A(vector3D_802240AC), 9, 1),
    OVL_ACTOR_BY_POS("swooper", A(vector3D_802240B8), 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "isk_02b", "サンボマミーx２"),
    BATTLE(A(Formation_01), "isk_02b", "サンボマミーx３"),
    BATTLE(A(Formation_02), "isk_04", "サンボマミー,バサバサ"),
    BATTLE(A(Formation_03), "isk_04", "サンボマミーx２,バサバサ"),
    BATTLE(A(Formation_04), "isk_04", "サンボマミーx２,バサバサx２"),
    BATTLE(A(Formation_05), "isk_04", "バサバサx２"),
    BATTLE(A(Formation_06), "isk_04", "バサバサx３"),
    BATTLE(A(Formation_07), "isk_02b", "ストーンワンワンx２"),
    BATTLE(A(Formation_08), "isk_02b", "ストーンワンワンx３"),
    BATTLE(A(Formation_09), "isk_02b", "メットx２"),
    BATTLE(A(Formation_0A), "isk_02b", "メットx４"),
    BATTLE(A(Formation_0B), "isk_05", "メット,メット（てんじょう）,バサバサ"),
    BATTLE(A(Formation_0C), "isk_05", "メット,バサバサ"),
    BATTLE(A(Formation_0D), "isk_05", "メット（てんじょう）,メット"),
    BATTLE(A(Formation_0E), "isk_05", "メット,メット(てんじょう)"),
    BATTLE(A(Formation_0F), "isk_05", "メット(てんじょう)x２"),
    BATTLE(A(Formation_10), "isk_05", "メット,メット(てんじょう)x２"),
    BATTLE(A(Formation_11), "isk_05", "メット(てんじょう)x３"),
    BATTLE(A(Formation_12), "isk_05", "メット(てんじょう)x４"),
    BATTLE(A(Formation_13), "isk_05", "メット(てんじょう)x２,バサバサ"),
    {},
};

StageList A(Stages) = {
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
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
