#include "battle/battle.h"


static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 9),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 9),
};

static Formation Formation_15 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_16 = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_D, 9),
};

static Formation Formation_17 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
};

static Formation Formation_18 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

static Formation Formation_19 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation Formation_1A = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

static Formation Formation_1B = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation Formation_1C = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_D, 7),
};

static Vec3i Formation_1D_pos1 = { 5, 0, -20 };

static Vec3i Formation_1D_pos2 = { 45, 0, -10 };

static Vec3i Formation_1D_pos3 = { 85, 0, 0 };

static Vec3i Formation_1D_pos4 = { 125, 0, 5 };

static Formation Formation_1D = {
    OVL_ACTOR_BY_POS("koopatrol", Formation_1D_pos1, 10),
    OVL_ACTOR_BY_POS("koopatrol", Formation_1D_pos2, 9),
    OVL_ACTOR_BY_POS("koopatrol", Formation_1D_pos3, 8),
    OVL_ACTOR_BY_POS("magikoopa", Formation_1D_pos4, 7),
};

static Formation Formation_1E = {
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

static Formation Formation_20 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 9),
};

static Formation Formation_21 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation Formation_22 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

static Formation Formation_23 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation Formation_24 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation Formation_25 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_D, 7),
};

static Formation Formation_26 = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_27 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_28 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_29 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_2A = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 8),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_D, 7),
};

static Formation Formation_2B = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

static Formation Formation_2C = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation Formation_2D = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_2E = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_2F = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_30 = {
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

static Formation Formation_31 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_B, 10),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 9),
};

static Formation Formation_32 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_A, 10),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_33 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_34 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

static Formation Formation_35 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

static Formation Formation_36 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

static Formation Formation_37 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_C, 9),
};

static Formation Formation_38 = {
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_NAMED_BY_IDX("magikoopa", flying, BTL_POS_AIR_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kpa_01", "Bony Beetle x2"),
    BATTLE(Formation_01, "kpa_01", "Bony Beetle x3"),
    BATTLE(Formation_02, "kpa_01", "Bony Beetle, Dry Bones x2"),
    BATTLE(Formation_03, "kpa_01", "Bony Beetle x2, Dry Bones"),
    BATTLE(Formation_04, "kpa_01", "Bony Beetle x2, Magikoopa"),
    BATTLE(Formation_05, "kpa_01", "Bony Beetle x3, Magikoopa"),
    BATTLE(Formation_06, "kpa_01", "Bony Beetle, Dry Bones, Bony Beetle, Magikoopa"),
    BATTLE(Formation_07, "kpa_01", "Dry Bones x2"),
    BATTLE(Formation_08, "kpa_01", "Dry Bones x3"),
    BATTLE(Formation_09, "kpa_01", "Dry Bones x4"),
    BATTLE(Formation_0A, "kpa_01", "Dry Bones, Ember x3"),
    BATTLE(Formation_0B, "kpa_01", "Dry Bones x2, Magikoopa"),
    BATTLE(Formation_0C, "kpa_01", "Dry Bones, Koopatrol x2"),
    BATTLE(Formation_0D, "kpa_01", "Dry Bones x2, Bony Beetle"),
    BATTLE(Formation_0E, "kpa_01", "Dry Bones x2, Bony Beetle x2"),
    BATTLE(Formation_0F, "kpa_01", "Hammer Bro x2"),
    BATTLE(Formation_10, "kpa_01", "Hammer Bro x3"),
    BATTLE(Formation_11, "kpa_01", "Hammer Bro, Koopatrol"),
    BATTLE(Formation_12, "kpa_01", "Hammer Bro x2, Koopatrol"),
    BATTLE(Formation_13, "kpa_01", "Hammer Bro, Koopatrol x2"),
    BATTLE(Formation_14, "kpa_01", "Hammer Bro, Dry Bones, Hammer Bro, Magikoopa"),
    BATTLE(Formation_15, "kpa_01", "Hammer Bro x2, Flying Magikoopa"),
    BATTLE(Formation_16, "kpa_01", "Hammer Bro x3, Flying Magikoopa"),
    BATTLE(Formation_17, "kpa_01", "Koopatrol"),
    BATTLE(Formation_18, "kpa_01", "Koopatrol x2"),
    BATTLE(Formation_19, "kpa_01", "Koopatrol x3"),
    BATTLE(Formation_1A, "kpa_01", "Koopatrol x4"),
    BATTLE(Formation_1B, "kpa_01", "Koopatrol, Hammer Bro"),
    BATTLE(Formation_1C, "kpa_01", "Koopatrol, Hammer Bro, Koopatrol, Hammer Bro"),
    BATTLE(Formation_1D, "kpa_01", "Koopatrol x3, Magikoopa"),
    BATTLE(Formation_1E, "kpa_01", "Koopatrol x2, Magikoopa x2"),
    BATTLE(Formation_20, "kpa_01", "Koopatrol, Bony Beetle"),
    BATTLE(Formation_21, "kpa_01", "Koopatrol x2, Bony Beetle"),
    BATTLE(Formation_22, "kpa_01", "Koopatrol, Bony Beetle x2"),
    BATTLE(Formation_23, "kpa_01", "Koopatrol, Bony Beetle, Koopatrol"),
    BATTLE(Formation_24, "kpa_01", "Koopatrol, Dry Bones x2"),
    BATTLE(Formation_25, "kpa_01", "Koopatrol x2, Magikoopa, Flying Magikoopa"),
    BATTLE(Formation_26, "kpa_01", "Koopatrol, Magikoopa, Koopatrol, Magikoopa"),
    BATTLE(Formation_27, "kpa_01", "Magikoopa x2"),
    BATTLE(Formation_28, "kpa_01", "Magikoopa x3"),
    BATTLE(Formation_29, "kpa_01", "Magikoopa, Flying Magikoopa x2"),
    BATTLE(Formation_2A, "kpa_01", "Magikoopa x2, Flying Magikoopa x2"),
    BATTLE(Formation_2B, "kpa_01", "Magikoopa, Koopatrol x3"),
    BATTLE(Formation_2C, "kpa_01", "Magikoopa x2, Dry Bones"),
    BATTLE(Formation_2D, "kpa_01", "Magikoopa, Bony Beetle, Magikoopa"),
    BATTLE(Formation_2E, "kpa_01", "Magikoopa, Bony Beetle x2, Magikoopa"),
    BATTLE(Formation_2F, "kpa_01", "Magikoopa x2, Flying Magikoopa"),
    BATTLE(Formation_30, "kpa_01", "Magikoopa, Koopatrol, Magikoopa, Koopatrol"),
    BATTLE(Formation_31, "kpa_01", "Flying Magikoopa x2"),
    BATTLE(Formation_32, "kpa_01", "Flying Magikoopa x3"),
    BATTLE(Formation_33, "kpa_01", "Flying Magikoopa, Magikoopa, Flying Magikoopa, Magikoopa"),
    BATTLE(Formation_34, "kpa_01", "Flying Magikoopa, Koopatrol x2"),
    BATTLE(Formation_35, "kpa_01", "Flying Magikoopa, Hammer Bro"),
    BATTLE(Formation_36, "kpa_01", "Flying Magikoopa, Dry Bones x2"),
    BATTLE(Formation_37, "kpa_01", "Flying Magikoopa, Koopatrol, Flying Magikoopa"),
    BATTLE(Formation_38, "kpa_01", "Flying Magikoopa, Hammer Bro x2, Flying Magikoopa"),
    {},
};

static StageList Stages = {
    STAGE("kpa_01", "kpa_01"),
    STAGE("kpa_01b", "kpa_01b"),
    STAGE("kpa_02", "kpa_02"),
    STAGE("kpa_03", "kpa_03"),
    STAGE("kpa_04", "kpa_04"),
    STAGE("kpa_04b", "kpa_04b"),
    STAGE("kpa_04c", "kpa_04c"),
    STAGE("kpa_05", "kpa_05"),
    STAGE("kpa_07", "kpa_07"),
    STAGE("kpa_08", "kpa_08"),
    STAGE("kpa_09", "kpa_09"),
    STAGE("kpa_11", "kpa_11"),
    STAGE("kpa_13", "kpa_13"),
    STAGE("kpa_14", "kpa_14"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
