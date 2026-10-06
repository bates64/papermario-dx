#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("kammy_koopa", BTL_POS_AIR_C, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kkj_02", "Kammy Koopa (Peach and Twink)"),
    {},
};

static StageList Stages = {
    STAGE("kpa_05", "kkj_02"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
