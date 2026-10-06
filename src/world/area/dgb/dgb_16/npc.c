#include "dgb_16.h"

#include "world/common/enemy/Clubba/napping.inc.c"

NpcData NpcData_Clubba_01[] = {
    {
        .id = NPC_Clubba_01,
        .pos = { -70.0f, 0.0f, -100.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -70, 0, -100 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 150, 0, -175 },
                .detectSize = { 430, 92 },
            }
        },
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_01_Hitbox),
};

NpcData NpcData_Clubba_02[] = {
    {
        .id = NPC_Clubba_02,
        .pos = { 0.0f, 0.0f, -235.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, -235 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 150, 0, -175 },
                .detectSize = { 430, 92 },
            }
        },
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_02_Hitbox),
};

NpcData NpcData_Clubba_03[] = {
    {
        .id = NPC_Clubba_03,
        .pos = { 70.0f, 0.0f, -100.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 70, 0, -100 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 150, 0, -175 },
                .detectSize = { 430, 92 },
            }
        },
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_03_Hitbox),
};

NpcData NpcData_Clubba_04[] = {
    {
        .id = NPC_Clubba_04,
        .pos = { 140.0f, 0.0f, -235.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 140, 0, -235 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 150, 0, -175 },
                .detectSize = { 430, 92 },
            }
        },
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_04_Hitbox),
};

NpcData NpcData_Clubba_05[] = {
    {
        .id = NPC_Clubba_05,
        .pos = { 210.0f, 0.0f, -100.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 210, 0, -100 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 150, 0, -175 },
                .detectSize = { 430, 92 },
            }
        },
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_05_Hitbox),
};

NpcData NpcData_Clubba_06[] = {
    {
        .id = NPC_Clubba_06,
        .pos = { 280.0f, 0.0f, -235.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 280, 0, -235 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_RECT,
                .detectPos  = { 150, 0, -175 },
                .detectSize = { 430, 92 },
            }
        },
        .settings = &NpcSettings_Clubba_Napping,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_06_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba_01, "dgb:clubba_4", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_02, "dgb:clubba_1", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_03, "dgb:clubba_1", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_04, "dgb:clubba_1", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_05, "dgb:clubba_2", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_06, "dgb:clubba_2", "dgb_03"),
    {}
};
