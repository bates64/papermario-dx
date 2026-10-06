#include "battle/battle.h"

static Vec3i BlueMinibossPos = { 14, 0, -10 };
static Vec3i RedMinibossPos  = { 54, 0,  32 };

static Formation goomba_bros = {
    OVL_ACTOR_BY_POS("blue_goomba_1", BlueMinibossPos, 10),
    OVL_ACTOR_BY_POS("red_goomba_1",  RedMinibossPos,  10),
};

static Vec3i KingBossPos = {  10, 0,  10 };
static Vec3i RedBossPos  = {  70, 0,  30 };
static Vec3i BlueBossPos = { 125, 0,  20 };
static Vec3i TreeBossPos = { -40, 0, -45 };

static Formation goomba_king = {
    OVL_ACTOR_BY_POS("goomba_king",   KingBossPos, 10),
    OVL_ACTOR_BY_POS("red_goomba_2",  RedBossPos,  10),
    OVL_ACTOR_BY_POS("blue_goomba_2", BlueBossPos, 10),
    OVL_ACTOR_BY_POS("goomnut_tree",  TreeBossPos, 10),
};

static BattleList Formations = {
    BATTLE(goomba_bros, "kmr_03"),
    BATTLE(goomba_king, "kmr_06"),
};

OVL_DEF_BATTLE_AREA(Formations);
