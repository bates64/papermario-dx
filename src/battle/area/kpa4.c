#include "battle/battle.h"


static Formation bombshell_bill_2 = {
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_C, 9),
};

static Formation bombshell_bill_3 = {
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bombshell_bill", BTL_POS_GROUND_C, 8),
};

static Vec3i blaster_pos_1 = { 70, 0, -20 };

static Vec3i blaster_pos_2 = { 100, 0, 0 };

static Formation bombshell_blaster_2 = {
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_1, 10),
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_2, 9),
};

static Vec3i pos_3 = { 130, 0, 25 };

static Formation bombshell_blaster_2_koopatrol_1 = {
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_1, 10),
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_2, 9),
    OVL_ACTOR_BY_POS("koopatrol", pos_3, 8),
};

static Formation bombshell_blaster_2_magikoopa_1 = {
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_1, 10),
    OVL_ACTOR_BY_POS("bombshell_blaster", blaster_pos_2, 9),
    OVL_ACTOR_BY_POS("magikoopa", pos_3, 8),
};

static BattleList Formations = {
    BATTLE(bombshell_bill_2, "kpa_01"),
    BATTLE(bombshell_bill_3, "kpa_01"),
    BATTLE(bombshell_blaster_2, "kpa_01"),
    BATTLE(bombshell_blaster_2_koopatrol_1, "kpa_01"),
    BATTLE(bombshell_blaster_2_magikoopa_1, "kpa_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
