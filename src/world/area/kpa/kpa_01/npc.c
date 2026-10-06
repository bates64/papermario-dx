#include "kpa_01.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BonyBeetle_01 = {
    .id = NPC_BonyBeetle_01,
    .pos = { 1740.0f, -215.0f, 60.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 1740, -215, 60 },
            .wanderSize = { 50 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 1740, -215, 60 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS,
    .animations = BONY_BEETLE_ANIMS,
};

NpcData NpcData_BonyBeetle_02 = {
    .id = NPC_BonyBeetle_02,
    .pos = { 243.0f, 5.0f, 230.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 243, 5, 230 },
            .wanderSize = { 50 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 243, 5, 230 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS,
    .animations = BONY_BEETLE_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BonyBeetle_01, "kpa:bony_beetle_2", "kpa_03"),
    NPC_GROUP(NpcData_BonyBeetle_02, "kpa:bony_beetle_3", "kpa_03"),
    {}
};
