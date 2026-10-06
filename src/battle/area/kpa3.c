#include "battle/battle.h"

static Formation anti_guy_3 = {
    OVL_ACTOR_BY_IDX("anti_guy:trio", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("anti_guy:trio", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("anti_guy:trio", BTL_POS_GROUND_C, 8),
};

static Formation duplighost_2 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 9),
};

static Formation duplighost_4 = {
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("duplighost", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(anti_guy_3, "kpa_01"),
    BATTLE(duplighost_2, "kpa_01"),
    BATTLE(duplighost_4, "kpa_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
