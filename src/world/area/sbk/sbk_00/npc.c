#include "sbk_00.h"

#include "world/common/enemy/Pokey/wander.inc.c"

NpcData NpcData_Pokey_01 = {
    .id = NPC_Pokey_01,
    .pos = { -40.0f, 0.0f, 160.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -40, 0, 160 },
            .wanderSize = { 100 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_FLYING,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_02 = {
    .id = NPC_Pokey_02,
    .pos = { 245.0f, 0.0f, 75.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 245, 0, 75 },
            .wanderSize = { 100 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 1000 },
        }
    },
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_FLYING,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Pokey_01, "sbk:pokey_1", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_02, "sbk:pokey_2", "sbk_02"),
    {}
};
