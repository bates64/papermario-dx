#include "battle/battle.h"


static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_D, 7),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 9),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("white_magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("red_magikoopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("yellow_magikoopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 9),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_D, 7),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_15 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_16 = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_C, 8),
};

static Formation Formation_17 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

static Formation Formation_18 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_19 = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("green_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static Formation Formation_1A = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

static Formation Formation_1B = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_1C = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_B, 10),
};

static Formation Formation_1D = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_1E = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_D, 7),
};

static Formation Formation_1F = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

static Formation Formation_20 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_D, 7),
};

static Formation Formation_21 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("lakitu", BTL_POS_AIR_C, 9),
};

static Formation Formation_22 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

static Formation Formation_23 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
};

static Formation Formation_24 = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_NAMED_BY_IDX("yellow_magikoopa", flying, BTL_POS_AIR_C, 8),
};

static BattleList Formations = {
    BATTLE(Formation_00, "flo_01", "Lakitu x2"),
    BATTLE(Formation_01, "flo_01", "Lakitu x3"),
    BATTLE(Formation_02, "flo_01", "Lakitu, Ruff Puff"),
    BATTLE(Formation_03, "flo_01", "Lakitu, Bzzap! x2"),
    BATTLE(Formation_04, "flo_01", "Lakitu, Bzzap!, Lakitu, Bzzap!"),
    BATTLE(Formation_05, "flo_01", "Lakitu, Crazee Dayzee"),
    BATTLE(Formation_06, "flo_01", "Lakitu, Spiny"),
    BATTLE(Formation_07, "flo_01", "Lakitu x2, Spiny x2"),
    BATTLE(Formation_08, "flo_01", "Lakitu x3, Spiny"),
    BATTLE(Formation_09, "flo_01", "Lakitu x2, White Magikoopa"),
    BATTLE(Formation_0A, "flo_01", "Lakitu x2, Red Magikoopa"),
    BATTLE(Formation_0B, "flo_01", "Lakitu x3, Yellow Magikoopa"),
    BATTLE(Formation_0C, "flo_01", "Spiny x2"),
    BATTLE(Formation_0D, "flo_01", "Spiny x3"),
    BATTLE(Formation_0E, "flo_01", "Spiny, Crazee Dayzee, Medi Guy"),
    BATTLE(Formation_0F, "flo_01", "Crazee Dayzee"),
    BATTLE(Formation_10, "flo_01", "Crazee Dayzee x2"),
    BATTLE(Formation_11, "flo_01", "Crazee Dayzee x3"),
    BATTLE(Formation_12, "flo_01", "Crazee Dayzee x4"),
    BATTLE(Formation_13, "flo_01", "Crazee Dayzee, Bzzap!"),
    BATTLE(Formation_14, "flo_01", "Crazee Dayzee, Bzzap! x2"),
    BATTLE(Formation_15, "flo_01", "Crazee Dayzee x2, Bzzap!"),
    BATTLE(Formation_16, "flo_01", "Crazee Dayzee x2, Amazy Dayzee"),
    BATTLE(Formation_17, "flo_01", "Bzzap! x2"),
    BATTLE(Formation_18, "flo_01", "Bzzap! x3"),
    BATTLE(Formation_19, "flo_01", "Bzzap! x2, Green Magikoopa (Flying)"),
    BATTLE(Formation_1A, "flo_01", "Bzzap!, Ruff Puff"),
    BATTLE(Formation_1B, "flo_01", "Bzzap!, Ruff Puff, Bzzap!"),
    BATTLE(Formation_1C, "flo_01", "Amazy Dayzee"),
    BATTLE(Formation_1D, "flo_01", "Amazy Dayzee, Bzzap! x2"),
    BATTLE(Formation_1E, "flo_01", "Amazy Dayzee x4"),
    BATTLE(Formation_1F, "flo_01", "Ruff Puff x2"),
    BATTLE(Formation_20, "flo_01", "Ruff Puff x4"),
    BATTLE(Formation_21, "flo_01", "Ruff Puff, Lakitu"),
    BATTLE(Formation_22, "flo_01", "Ruff Puff x2, Bzzap!"),
    BATTLE(Formation_23, "flo_01", "Ruff Puff x2, Crazee Dayzee"),
    BATTLE(Formation_24, "flo_01", "Ruff Puff x2, Yellow Magikoopa (Flying)"),
    {},
};

static StageList Stages = {
    STAGE("flo_01", "flo_01"),
    STAGE("flo_01b", "flo_01b"),
    STAGE("flo_01c", "flo_01c"),
    STAGE("flo_02", "flo_02"),
    STAGE("flo_02b", "flo_02b"),
    STAGE("flo_02c", "flo_02c"),
    STAGE("flo_03", "flo_03"),
    STAGE("flo_04", "flo_04"),
    STAGE("flo_05", "flo_05"),
    STAGE("flo_06", "flo_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
