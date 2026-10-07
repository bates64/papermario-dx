#include "kzn_07.h"
#include "effects.h"

#include "world/common/enemy/LavaBubble/wander.inc.c"

NpcData NpcData_LavaBubble_01 = {
    .id = NPC_Bubble_01,
    .pos = { -200.0f, 50.0f, 150.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -200, 50, 150 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -200, 50, 150 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_LavaBubble_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = LAVA_BUBBLE_DROPS,
    .animations = LAVA_BUBBLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_LavaBubble_02 = {
    .id = NPC_Bubble_02,
    .pos = { -250.0f, 80.0f, 50.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -250, 80, 50 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -250, 80, 50 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_LavaBubble_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = LAVA_BUBBLE_DROPS,
    .animations = LAVA_BUBBLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_LavaBubble_01, "kzn:lava_bubble_2_red_magikoopa_1", "kzn_01:b"),
    NPC_GROUP(NpcData_LavaBubble_02, "kzn:lava_bubble_2_white_magikoopa_1", "kzn_01:b"),
    {}
};
