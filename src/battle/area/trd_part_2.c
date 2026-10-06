#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", green, BTL_POS_GROUND_A, 10),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", yellow, BTL_POS_GROUND_A, 9),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", black, BTL_POS_GROUND_A, 8),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", red, BTL_POS_GROUND_A, 7),
    OVL_ACTOR_NAMED_BY_IDX("koopa_bros", fake_bowser, BTL_POS_GROUND_D, 6),
};

static BattleList Formations = {
    BATTLE(Formation_00, "trd_00", "Koopa Bros."),
    {},
};

static StageList Stages = {
    STAGE("trd_00",  "trd_00"),
    STAGE("trd_01",  "trd_01"),
    STAGE("trd_02",  "trd_02"),
    STAGE("trd_02b", "trd_02b"),
    STAGE("trd_03",  "trd_03"),
    STAGE("trd_04",  "trd_04"),
    STAGE("trd_05",  "trd_05"),
    STAGE("trd_05b", "trd_05b"),
    STAGE("trd_05c", "trd_05c"),
    STAGE("trd_05d", "trd_05d"),
    STAGE("trd_05e", "trd_05e"),
    STAGE("trd_05f", "trd_05f"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
