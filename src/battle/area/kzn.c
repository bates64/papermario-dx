#include "battle/battle.h"


static Formation lava_bubble_2 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 9),
};

static Formation lava_bubble_3 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
};

static Formation lava_bubble_4 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_D, 7),
};

static Formation lava_bubble_1_spike_top_3 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

static Formation lava_bubble_2_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation lava_bubble_2_red_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("red_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation lava_bubble_2_white_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("white_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation lava_bubble_2_spike_top_1 = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation spike_top_2 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 9),
};

static Formation spike_top_1_lava_bubble_1 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 9),
};

static Formation spike_top_2_lava_bubble_1 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
};

static Formation spike_top_1_putrid_piranha_1 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

static Formation spike_top_2_putrid_piranha_1 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation spike_top_2_putrid_piranha_2 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_D, 7),
};

static Formation spike_top_1_lava_bubble_3 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_D, 7),
};

static Formation putrid_piranha_2 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

static Formation putrid_piranha_3 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation putrid_piranha_1_lava_bubble_1_putrid_piranha_1 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation putrid_piranha_2_spike_top_1 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation putrid_piranha_1_spike_top_1_putrid_piranha_1 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

static Formation putrid_piranha_1_mixed_14 = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(lava_bubble_2, "kzn_01"),
    BATTLE(lava_bubble_3, "kzn_01"),
    BATTLE(lava_bubble_4, "kzn_01"),
    BATTLE(lava_bubble_1_spike_top_3, "kzn_01"),
    BATTLE(lava_bubble_2_medi_guy_1, "kzn_01"),
    BATTLE(lava_bubble_2_red_magikoopa_1, "kzn_01"),
    BATTLE(lava_bubble_2_white_magikoopa_1, "kzn_01"),
    BATTLE(lava_bubble_2_spike_top_1, "kzn_01"),
    BATTLE(spike_top_2, "kzn_01"),
    BATTLE(spike_top_1_lava_bubble_1, "kzn_01"),
    BATTLE(spike_top_2_lava_bubble_1, "kzn_01"),
    BATTLE(spike_top_1_putrid_piranha_1, "kzn_01"),
    BATTLE(spike_top_2_putrid_piranha_1, "kzn_01"),
    BATTLE(spike_top_2_putrid_piranha_2, "kzn_01"),
    BATTLE(spike_top_1_lava_bubble_3, "kzn_01"),
    BATTLE(putrid_piranha_2, "kzn_01"),
    BATTLE(putrid_piranha_3, "kzn_01"),
    BATTLE(putrid_piranha_1_lava_bubble_1_putrid_piranha_1, "kzn_01"),
    BATTLE(putrid_piranha_2_spike_top_1, "kzn_01"),
    BATTLE(putrid_piranha_1_spike_top_1_putrid_piranha_1, "kzn_01"),
    BATTLE(putrid_piranha_1_mixed_14, "kzn_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
