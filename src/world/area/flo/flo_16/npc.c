#include "flo_16.h"
#include "entity.h"

#include "world/common/enemy/RuffPuff/wander.inc.c"

NpcData NpcData_RuffPuff_01 = {
    .id = NPC_RuffPuff_01,
    .pos = { 440.0f, 145.0f, 15.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 440, 145, 15 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_RECT,
            .detectPos  = { 485, 145, 55 },
            .detectSize = { 225, 95 },
        }
    },
    .settings = &NpcSettings_RuffPuff_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = RUFF_PUFF_DROPS,
    .animations = RUFF_PUFF_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_RuffPuff_02 = {
    .id = NPC_RuffPuff_02,
    .pos = { 600.0f, 145.0f, 15.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 600, 145, 15 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_RECT,
            .detectPos  = { 485, 145, 55 },
            .detectSize = { 225, 95 },
        }
    },
    .settings = &NpcSettings_RuffPuff_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = RUFF_PUFF_DROPS,
    .animations = RUFF_PUFF_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_RuffPuff_01, "flo:ruff_puff_2_yellow_magikoopa_flying_1", "flo_02c"),
    NPC_GROUP(NpcData_RuffPuff_02, "flo:ruff_puff_4", "flo_02c"),
    {}
};
