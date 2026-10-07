#include "pra_10.h"

#include "world/common/enemy/Swooper/wander.inc.c"

EvtScript EVS_NpcInit_Swoopula = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_REFLECT_FLOOR, true)
    Return
    End
};

NpcData NpcData_Swoopula_01 = {
    .id = NPC_Swoopula_01,
    .pos = { 166.0f, 130.0f, 90.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 166, 130, 90 },
            .wanderSize = { 0 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 166, 130, 90 },
            .detectSize = { 250 },
        }
    },
    .init = &EVS_NpcInit_Swoopula,
    .settings = &NpcSettings_Swoopula_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = SWOOPULA_DROPS,
    .animations = SWOOPULA_ANIMS,
};

NpcData NpcData_Swoopula_02 = {
    .id = NPC_Swoopula_02,
    .pos = { 358.0f, 130.0f, 75.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 358, 130, 75 },
            .wanderSize = { 0 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 358, 130, 75 },
            .detectSize = { 250 },
        }
    },
    .init = &EVS_NpcInit_Swoopula,
    .settings = &NpcSettings_Swoopula_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = SWOOPULA_DROPS,
    .animations = SWOOPULA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Swoopula_01, "pra:swoopula_3", "pra_01"),
    NPC_GROUP(NpcData_Swoopula_02, "pra:swoopula_3_yellow_magikoopa_flying_1", "pra_01"),
    {}
};
