#include "battle/battle.h"


static Formation bony_beetle_2 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 9),
};

static Formation bony_beetle_3 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation bony_beetle_1_dry_bones_2 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation bony_beetle_2_dry_bones_1 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation bony_beetle_2_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation bony_beetle_3_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation bony_beetle_1_dry_bones_1_bony_beetle_1_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation dry_bones_2 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 9),
};

static Formation dry_bones_3 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation dry_bones_4 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_D, 7),
};

static Formation dry_bones_1_ember_3 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_D, 7),
};

static Formation dry_bones_2_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation dry_bones_1_koopatrol_2 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation dry_bones_2_bony_beetle_1 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation dry_bones_2_bony_beetle_2 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_D, 7),
};

static Formation hammer_bro_2 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation hammer_bro_3 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
};

static Formation hammer_bro_1_koopatrol_1 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

static Formation hammer_bro_2_koopatrol_1 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation hammer_bro_1_koopatrol_2 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation hammer_bro_1_dry_bones_1_hammer_bro_1_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 9),
};

static Formation hammer_bro_2_flying_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 8),
};

static Formation hammer_bro_3_flying_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_D, 9),
};

static Formation koopatrol_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
};

static Formation koopatrol_2 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

static Formation koopatrol_3 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation koopatrol_4 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

static Formation koopatrol_1_hammer_bro_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation koopatrol_1_hammer_bro_1_koopatrol_1_hammer_bro_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_D, 7),
};

static Vec3i Formation_1D_pos1 = { 5, 0, -20 };

static Vec3i Formation_1D_pos2 = { 45, 0, -10 };

static Vec3i Formation_1D_pos3 = { 85, 0, 0 };

static Vec3i Formation_1D_pos4 = { 125, 0, 5 };

static Formation koopatrol_3_magikoopa_1 = {
    OVL_ACTOR_BY_POS("koopatrol", Formation_1D_pos1, 10),
    OVL_ACTOR_BY_POS("koopatrol", Formation_1D_pos2, 9),
    OVL_ACTOR_BY_POS("koopatrol", Formation_1D_pos3, 8),
    OVL_ACTOR_BY_POS("magikoopa", Formation_1D_pos4, 7),
};

static Formation koopatrol_2_magikoopa_2 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_1F = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation koopatrol_1_bony_beetle_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 9),
};

static Formation koopatrol_2_bony_beetle_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation koopatrol_1_bony_beetle_2 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation koopatrol_1_bony_beetle_1_koopatrol_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation koopatrol_1_dry_bones_2 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation koopatrol_2_magikoopa_1_flying_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_D, 7),
};

static Formation koopatrol_1_magikoopa_1_koopatrol_1_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation magikoopa_2 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation magikoopa_3 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation magikoopa_1_flying_magikoopa_2 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 8),
};

static Formation magikoopa_2_flying_magikoopa_2 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_D, 7),
};

static Formation magikoopa_1_koopatrol_3 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

static Formation magikoopa_2_dry_bones_1 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation magikoopa_1_bony_beetle_1_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation magikoopa_1_bony_beetle_2_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation magikoopa_2_flying_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 8),
};

static Formation magikoopa_1_koopatrol_1_magikoopa_1_koopatrol_1 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

static Formation flying_magikoopa_2 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 9),
};

static Formation flying_magikoopa_3 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 8),
};

static Formation flying_magikoopa_1_mixed_32 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation flying_magikoopa_1_koopatrol_2 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation flying_magikoopa_1_hammer_bro_1 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation flying_magikoopa_1_dry_bones_2 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation flying_magikoopa_1_koopatrol_1_flying_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_C, 9),
};

static Formation flying_magikoopa_1_hammer_bro_2_flying_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa:flying", BTL_POS_AIR_D, 7),
};

static BattleList Formations = {
    BATTLE(bony_beetle_2, "kpa_01"),
    BATTLE(bony_beetle_3, "kpa_01"),
    BATTLE(bony_beetle_1_dry_bones_2, "kpa_01"),
    BATTLE(bony_beetle_2_dry_bones_1, "kpa_01"),
    BATTLE(bony_beetle_2_magikoopa_1, "kpa_01"),
    BATTLE(bony_beetle_3_magikoopa_1, "kpa_01"),
    BATTLE(bony_beetle_1_dry_bones_1_bony_beetle_1_magikoopa_1, "kpa_01"),
    BATTLE(dry_bones_2, "kpa_01"),
    BATTLE(dry_bones_3, "kpa_01"),
    BATTLE(dry_bones_4, "kpa_01"),
    BATTLE(dry_bones_1_ember_3, "kpa_01"),
    BATTLE(dry_bones_2_magikoopa_1, "kpa_01"),
    BATTLE(dry_bones_1_koopatrol_2, "kpa_01"),
    BATTLE(dry_bones_2_bony_beetle_1, "kpa_01"),
    BATTLE(dry_bones_2_bony_beetle_2, "kpa_01"),
    BATTLE(hammer_bro_2, "kpa_01"),
    BATTLE(hammer_bro_3, "kpa_01"),
    BATTLE(hammer_bro_1_koopatrol_1, "kpa_01"),
    BATTLE(hammer_bro_2_koopatrol_1, "kpa_01"),
    BATTLE(hammer_bro_1_koopatrol_2, "kpa_01"),
    BATTLE(hammer_bro_1_dry_bones_1_hammer_bro_1_magikoopa_1, "kpa_01"),
    BATTLE(hammer_bro_2_flying_magikoopa_1, "kpa_01"),
    BATTLE(hammer_bro_3_flying_magikoopa_1, "kpa_01"),
    BATTLE(koopatrol_1, "kpa_01"),
    BATTLE(koopatrol_2, "kpa_01"),
    BATTLE(koopatrol_3, "kpa_01"),
    BATTLE(koopatrol_4, "kpa_01"),
    BATTLE(koopatrol_1_hammer_bro_1, "kpa_01"),
    BATTLE(koopatrol_1_hammer_bro_1_koopatrol_1_hammer_bro_1, "kpa_01"),
    BATTLE(koopatrol_3_magikoopa_1, "kpa_01"),
    BATTLE(koopatrol_2_magikoopa_2, "kpa_01"),
    BATTLE(koopatrol_1_bony_beetle_1, "kpa_01"),
    BATTLE(koopatrol_2_bony_beetle_1, "kpa_01"),
    BATTLE(koopatrol_1_bony_beetle_2, "kpa_01"),
    BATTLE(koopatrol_1_bony_beetle_1_koopatrol_1, "kpa_01"),
    BATTLE(koopatrol_1_dry_bones_2, "kpa_01"),
    BATTLE(koopatrol_2_magikoopa_1_flying_magikoopa_1, "kpa_01"),
    BATTLE(koopatrol_1_magikoopa_1_koopatrol_1_magikoopa_1, "kpa_01"),
    BATTLE(magikoopa_2, "kpa_01"),
    BATTLE(magikoopa_3, "kpa_01"),
    BATTLE(magikoopa_1_flying_magikoopa_2, "kpa_01"),
    BATTLE(magikoopa_2_flying_magikoopa_2, "kpa_01"),
    BATTLE(magikoopa_1_koopatrol_3, "kpa_01"),
    BATTLE(magikoopa_2_dry_bones_1, "kpa_01"),
    BATTLE(magikoopa_1_bony_beetle_1_magikoopa_1, "kpa_01"),
    BATTLE(magikoopa_1_bony_beetle_2_magikoopa_1, "kpa_01"),
    BATTLE(magikoopa_2_flying_magikoopa_1, "kpa_01"),
    BATTLE(magikoopa_1_koopatrol_1_magikoopa_1_koopatrol_1, "kpa_01"),
    BATTLE(flying_magikoopa_2, "kpa_01"),
    BATTLE(flying_magikoopa_3, "kpa_01"),
    BATTLE(flying_magikoopa_1_mixed_32, "kpa_01"),
    BATTLE(flying_magikoopa_1_koopatrol_2, "kpa_01"),
    BATTLE(flying_magikoopa_1_hammer_bro_1, "kpa_01"),
    BATTLE(flying_magikoopa_1_dry_bones_2, "kpa_01"),
    BATTLE(flying_magikoopa_1_koopatrol_1_flying_magikoopa_1, "kpa_01"),
    BATTLE(flying_magikoopa_1_hammer_bro_2_flying_magikoopa_1, "kpa_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
