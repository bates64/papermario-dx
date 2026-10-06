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

static Formation duplighost_2 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 9),
};

static Formation gulpit_2 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 20),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 19),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_1[4], 5, 1),
};

static Formation gulpit_3 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_2[4], 5, 1),
};

static Formation gulpit_2_frost_piranha_1 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_3[4], 5, 1),
};

static Formation gulpit_1_frost_piranha_1_gulpit_1 = {
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_A, 20),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 19),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 18),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_4[4], 5, 1),
};

static Formation gulpit_1_frost_piranha_1_gulpit_1_frost_piranha_1 = {
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

static Formation frost_piranha_2 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 9),
};

static Formation frost_piranha_4 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_D, 7),
};

static Formation frost_piranha_2_gulpit_1 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_6[4], 5, 1),
};

static Formation frost_piranha_1_gulpit_1_frost_piranha_1 = {
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gulpit", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[0], 9),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[1], 8),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[2], 7, 1),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[3], 6),
    OVL_ACTOR_BY_POS("gulpit_rocks", pos_rocks_7[4], 5, 1),
};

static Formation frost_piranha_1_gulpit_1_frost_piranha_1_gulpit_1 = {
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

static Formation white_clubba_2 = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 9),
};

static Formation white_clubba_1_mixed_0c = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_D, 7),
};

static Formation white_clubba_1_mixed_0d = {
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("frost_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("white_clubba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("gray_magikoopa", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(duplighost_2, "sam_01"),
    BATTLE(gulpit_2, "sam_01"),
    BATTLE(gulpit_3, "sam_01"),
    BATTLE(gulpit_2_frost_piranha_1, "sam_01"),
    BATTLE(gulpit_1_frost_piranha_1_gulpit_1, "sam_01"),
    BATTLE(gulpit_1_frost_piranha_1_gulpit_1_frost_piranha_1, "sam_01"),
    BATTLE(frost_piranha_2, "sam_01"),
    BATTLE(frost_piranha_4, "sam_01"),
    BATTLE(frost_piranha_2_gulpit_1, "sam_01"),
    BATTLE(frost_piranha_1_gulpit_1_frost_piranha_1, "sam_01"),
    BATTLE(frost_piranha_1_gulpit_1_frost_piranha_1_gulpit_1, "sam_01"),
    BATTLE(white_clubba_2, "sam_01"),
    BATTLE(white_clubba_1_mixed_0c, "sam_01"),
    BATTLE(white_clubba_1_mixed_0d, "sam_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
