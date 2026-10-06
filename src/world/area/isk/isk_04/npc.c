#include "isk_04.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BuzzyBeetle_01 = {
    .id = NPC_BuzzyBeetle_01,
    .pos = { 561.0f, 25.0f, 47.0f },
    .yaw = 355,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 561, 25, 47 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 606, 25, 94 },
            .detectSize = { 80 },
        }
    },
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcData NpcData_BuzzyBeetle_02 = {
    .id = NPC_BuzzyBeetle_02,
    .pos = { 608.0f, -260.0f, -158.0f },
    .yaw = 175,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 608, -260, -158 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 596, -260, -203 },
            .detectSize = { 80 },
        }
    },
    .settings = &NpcSettings_BuzzyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = ISK_BUZZY_BEETLE_DROPS,
    .animations = BUZZY_BEETLE_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BuzzyBeetle_01, "isk_part_1:buzzy_beetle_2", "isk_02b"),
    NPC_GROUP(NpcData_BuzzyBeetle_02, "isk_part_1:buzzy_beetle_2", "isk_02b"),
    {}
};
