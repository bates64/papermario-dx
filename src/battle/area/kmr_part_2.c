#include "battle/battle.h"

static Vec3i BlueMinibossPos = { 14, 0, -10 };
static Vec3i RedMinibossPos  = { 54, 0,  32 };

static Formation Formation_00 = {
    OVL_ACTOR_BY_POS("blue_goomba_1", BlueMinibossPos, 10),
    OVL_ACTOR_BY_POS("red_goomba_1",  RedMinibossPos,  10),
};

static Vec3i KingBossPos = {  10, 0,  10 };
static Vec3i RedBossPos  = {  70, 0,  30 };
static Vec3i BlueBossPos = { 125, 0,  20 };
static Vec3i TreeBossPos = { -40, 0, -45 };

static Formation Formation_01 = {
    OVL_ACTOR_BY_POS("goomba_king",   KingBossPos, 10),
    OVL_ACTOR_BY_POS("red_goomba_2",  RedBossPos,  10),
    OVL_ACTOR_BY_POS("blue_goomba_2", BlueBossPos, 10),
    OVL_ACTOR_BY_POS("goomnut_tree",  TreeBossPos, 10),
};

static BattleList Formations = {
    BATTLE(Formation_00, "kmr_03", "Red Goomba, Blue Goomba"),
    BATTLE(Formation_01, "kmr_06", "Goomba King, Red Goomba, Blue Goomba"),
    {},
};

static StageList Stages = {
    STAGE("kmr_02", "kmr_02"),
    STAGE("kmr_03", "kmr_03"),
    STAGE("kmr_04", "kmr_04"),
    STAGE("kmr_05", "kmr_05"),
    STAGE("kmr_06", "kmr_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
