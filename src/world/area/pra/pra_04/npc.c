#include "pra_04.h"

#include "world/common/enemy/Swooper/wander.inc.c"

NpcData NpcData_Swoopula = {
    .id = NPC_Swoopula,
    .pos = { 50.0f, 130.0f, 75.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 50, 130, 75 },
            .wanderSize = { 0 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 50, 130, 75 },
            .detectSize = { 200 },
        }
    },
    .settings = &NpcSettings_Swoopula_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = SWOOPULA_DROPS,
    .animations = SWOOPULA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Swoopula, "pra3:swoopula_2_duplighost_1", "pra_01"),
    {}
};
