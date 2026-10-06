#include "hos_02.h"

#include "world/common/enemy/Ember/wander.inc.c"

NpcData NpcData_Ember = {
    .id = NPC_Ember_01,
    .pos = { -410.0f, -15.0f, 260.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -410, -15, 260 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -410, -15, 260 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Ember_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = EMBER_DROPS,
    .animations = EMBER_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Ember_02 = {
    .id = NPC_Ember_02,
    .pos = { 220.0f, 200.0f, -205.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 220, 200, -205 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 220, 200, -205 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Ember_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = EMBER_DROPS,
    .animations = EMBER_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Ember_03 = {
    .id = NPC_Ember_03,
    .pos = { -135.0f, 370.0f, 270.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -135, 370, 270 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -135, 370, 270 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Ember_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = EMBER_DROPS,
    .animations = EMBER_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Ember, "hos:ember_2", "hos_01"),
    NPC_GROUP(NpcData_Ember_02, "hos:ember_2", "hos_01"),
    NPC_GROUP(NpcData_Ember_03, "hos:ember_2", "hos_01"),
    {}
};
