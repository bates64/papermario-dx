#include "kmr_06.h"

#include "world/common/enemy/SpikedGoomba/wander.inc.c"
#include "world/common/enemy/Paragoomba/wander.inc.c"

NpcData NpcData_SpikedGoomba = {
    .id = NPC_SpikedGoomba,
    .pos = { 160.0f, 0.0f, 30.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_RECT,
            .centerPos  = { 160, 0, 30 },
            .wanderSize = { 30, 20 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 160, 0, 30 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_SpikedGoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = SPIKED_GOOMBA_DROPS,
    .animations = SPIKED_GOOMBA_ANIMS,
};

NpcData NpcData_Paragoomba = {
    .id = NPC_Paragoomba,
    .pos = { 525.0f, 60.0f, 15.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 525, 60, 15 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 525, 60, 15 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_Paragoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PARAGOOMBA_DROPS,
    .animations = PARAGOOMBA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpikedGoomba, "kmr_part_1:spiked_goomba_1_goomba_1", "kmr_04"),
    NPC_GROUP(NpcData_Paragoomba, "kmr_part_1:paragoomba_3", "kmr_04"),
    {}
};
