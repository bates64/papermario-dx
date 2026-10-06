#include "tik_24.h"

#include "world/common/enemy/DarkTroopa/wander.inc.c"

NpcData NpcData_DarkTroopa_01 = {
    .id = NPC_DarkTroopa_01,
    .pos = { -75.0f, -10.0f, 50.0f },
    .yaw = 90,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -75, -10, 50 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -75, -10, 50 },
            .detectSize = { 250 },
        }
    },
    .settings = &NpcSettings_DarkTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = DARK_TROOPA_DROPS,
    .animations = DARK_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_DarkTroopa_02 = {
    .id = NPC_DarkTroopa_02,
    .pos = { 175.0f, -10.0f, -50.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 175, -10, -50 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 175, -10, -50 },
            .detectSize = { 250 },
        }
    },
    .settings = &NpcSettings_DarkTroopa_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = DARK_TROOPA_DROPS,
    .animations = DARK_TROOPA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_DarkTroopa_01, "tik:dark_koopa_1_spiny_2", "tik_01"),
    NPC_GROUP(NpcData_DarkTroopa_02, "tik:dark_koopa_1_spiny_1_dark_koopa_1_spiny_1", "tik_01"),
    {}
};
