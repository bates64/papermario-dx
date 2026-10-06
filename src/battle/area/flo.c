#include "battle/battle.h"


static Formation lakitu_2 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 9),
};

static Formation lakitu_3 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
};

static Formation lakitu_1_ruff_puff_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

static Formation lakitu_1_bzzap_2 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation lakitu_1_bzzap_1_lakitu_1_bzzap_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_D, 7),
};

static Formation lakitu_1_crazee_dayzee_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 9),
};

static Formation lakitu_1_spiny_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

static Formation lakitu_2_spiny_2 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static Formation lakitu_3_spiny_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static Formation lakitu_2_white_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation lakitu_2_red_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation lakitu_3_yellow_magikoopa_1 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("yellow_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation spiny_2 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

static Formation spiny_3 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

static Formation spiny_1_crazee_dayzee_1_medi_guy_1 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation crazee_dayzee_1 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
};

static Formation crazee_dayzee_2 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 9),
};

static Formation crazee_dayzee_3 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
};

static Formation crazee_dayzee_4 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_D, 7),
};

static Formation crazee_dayzee_1_bzzap_1 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

static Formation crazee_dayzee_1_bzzap_2 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation crazee_dayzee_2_bzzap_1 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation crazee_dayzee_2_amazy_dayzee_1 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_C, 8),
};

static Formation bzzap_2 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

static Formation bzzap_3 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation bzzap_2_green_magikoopa_flying_1 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("green_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation bzzap_1_ruff_puff_1 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

static Formation bzzap_1_ruff_puff_1_bzzap_1 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation amazy_dayzee_1 = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_B, 10),
};

static Formation amazy_dayzee_1_bzzap_2 = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation amazy_dayzee_4 = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_D, 7),
};

static Formation ruff_puff_2 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

static Formation ruff_puff_4 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_D, 7),
};

static Formation ruff_puff_1_lakitu_1 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 9),
};

static Formation ruff_puff_2_bzzap_1 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation ruff_puff_2_crazee_dayzee_1 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
};

static Formation ruff_puff_2_yellow_magikoopa_flying_1 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("yellow_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static BattleList Formations = {
    BATTLE(lakitu_2, "flo_01"),
    BATTLE(lakitu_3, "flo_01"),
    BATTLE(lakitu_1_ruff_puff_1, "flo_01"),
    BATTLE(lakitu_1_bzzap_2, "flo_01"),
    BATTLE(lakitu_1_bzzap_1_lakitu_1_bzzap_1, "flo_01"),
    BATTLE(lakitu_1_crazee_dayzee_1, "flo_01"),
    BATTLE(lakitu_1_spiny_1, "flo_01"),
    BATTLE(lakitu_2_spiny_2, "flo_01"),
    BATTLE(lakitu_3_spiny_1, "flo_01"),
    BATTLE(lakitu_2_white_magikoopa_1, "flo_01"),
    BATTLE(lakitu_2_red_magikoopa_1, "flo_01"),
    BATTLE(lakitu_3_yellow_magikoopa_1, "flo_01"),
    BATTLE(spiny_2, "flo_01"),
    BATTLE(spiny_3, "flo_01"),
    BATTLE(spiny_1_crazee_dayzee_1_medi_guy_1, "flo_01"),
    BATTLE(crazee_dayzee_1, "flo_01"),
    BATTLE(crazee_dayzee_2, "flo_01"),
    BATTLE(crazee_dayzee_3, "flo_01"),
    BATTLE(crazee_dayzee_4, "flo_01"),
    BATTLE(crazee_dayzee_1_bzzap_1, "flo_01"),
    BATTLE(crazee_dayzee_1_bzzap_2, "flo_01"),
    BATTLE(crazee_dayzee_2_bzzap_1, "flo_01"),
    BATTLE(crazee_dayzee_2_amazy_dayzee_1, "flo_01"),
    BATTLE(bzzap_2, "flo_01"),
    BATTLE(bzzap_3, "flo_01"),
    BATTLE(bzzap_2_green_magikoopa_flying_1, "flo_01"),
    BATTLE(bzzap_1_ruff_puff_1, "flo_01"),
    BATTLE(bzzap_1_ruff_puff_1_bzzap_1, "flo_01"),
    BATTLE(amazy_dayzee_1, "flo_01"),
    BATTLE(amazy_dayzee_1_bzzap_2, "flo_01"),
    BATTLE(amazy_dayzee_4, "flo_01"),
    BATTLE(ruff_puff_2, "flo_01"),
    BATTLE(ruff_puff_4, "flo_01"),
    BATTLE(ruff_puff_1_lakitu_1, "flo_01"),
    BATTLE(ruff_puff_2_bzzap_1, "flo_01"),
    BATTLE(ruff_puff_2_crazee_dayzee_1, "flo_01"),
    BATTLE(ruff_puff_2_yellow_magikoopa_flying_1, "flo_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
