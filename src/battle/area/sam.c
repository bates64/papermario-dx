#include "battle/battle.h"

static Vec3i pos_rocks_1[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_2[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_3[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_4[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_5[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_6[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_7[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Vec3i pos_rocks_8[] = {
    { -35, 0, -52 },
    { -20, 0, -50 },
    { -17, 0, -40 },
    { -7, 0, -48 },
    { -28, 0, -46 },
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 9),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 20),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 19),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[4], 5, 1),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[4], 5, 1),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[4], 5, 1),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[4], 5, 1),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_D, 17),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_5[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_5[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_5[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_5[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_5[4], 5, 1),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 9),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_D, 7),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[4], 5, 1),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[4], 5, 1),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_D, 7),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_8[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_8[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_8[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_8[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_8[4], 5, 1),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_01, "sam_01", "Duplighost x2"),
    BATTLE(Formation_02, "sam_01", "Gulpit x2"),
    BATTLE(Formation_03, "sam_01", "Gulpit x3"),
    BATTLE(Formation_04, "sam_01", "Gulpit x2, Frost Piranha"),
    BATTLE(Formation_05, "sam_01", "Gulpit, Frost Piranha, Gulpit"),
    BATTLE(Formation_06, "sam_01", "Gulpit, Frost Piranha, Gulpit, Frost Piranha"),
    BATTLE(Formation_07, "sam_01", "Frost Piranha x2"),
    BATTLE(Formation_08, "sam_01", "Frost Piranha x4"),
    BATTLE(Formation_09, "sam_01", "Frost Piranha x2, Gulpit"),
    BATTLE(Formation_0A, "sam_01", "Frost Piranha, Gulpit, Frost Piranha"),
    BATTLE(Formation_0B, "sam_01", "Frost Piranha, Gulpit, Frost Piranha, Gulpit"),
    BATTLE(Formation_0C, "sam_01", "White Clubba x2"),
    BATTLE(Formation_0D, "sam_01", "White Clubba, Frost Piranha, White Clubba, Frost Piranha"),
    BATTLE(Formation_0E, "sam_01", "White Clubba, Frost Piranha, White Clubba, Gray Magikoopa"),
    {},
};

static StageList Stages = {
    STAGE("sam_01", "sam_01"),
    STAGE("sam_02", "sam_02"),
    STAGE("sam_02b", "sam_02b"),
    STAGE("sam_02c", "sam_02c"),
    STAGE("sam_02d", "sam_02d"),
    STAGE("sam_03", "sam_03"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
