#include "tik_05.h"

#include "world/common/enemy/SpikedGloomba/wander.inc.c"

NpcData NpcData_SpikedGloomba_01 = {
    .id = NPC_SpikedGoomba_01,
    .pos = { 220.0f, -10.0f, -80.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 220, -10, -80 },
            .wanderSize = { 20 },
            .detectShape = SHAPE_RECT,
            .detectPos  = { 160, 0, -20 },
            .detectSize = { 180, 100 },
        }
    },
    .settings = &NpcSettings_SpikedGloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = SPIKED_GLOOMBA_DROPS,
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcData NpcData_SpikedGloomba_02 = {
    .id = NPC_SpikedGoomba_02,
    .pos = { 130.0f, -10.0f, 45.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 130, -10, 45 },
            .wanderSize = { 20 },
            .detectShape = SHAPE_RECT,
            .detectPos  = { 160, 0, -20 },
            .detectSize = { 180, 100 },
        }
    },
    .settings = &NpcSettings_SpikedGloomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = SPIKED_GLOOMBA_DROPS,
    .animations = SPIKED_GLOOMBA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpikedGloomba_01, "tik:spiked_gloomba_1_buzzy_beetle_2", "tik_01"),
    NPC_GROUP(NpcData_SpikedGloomba_02, "tik:spiked_gloomba_1_mixed_12", "tik_01"),
    {}
};
