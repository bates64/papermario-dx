#include "sam_10.h"

#include "world/common/enemy/FrostClubba/wander.inc.c"

NpcData NpcData_Clubba[] = {
    {
        .id = NPC_FrostClubba,
        .pos = { 575.0f, 480.0f, -50.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 575, 480, -50 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 575, 480, -50 },
                .detectSize = { 200 },
            }
        },
        .settings = &NpcSettings_FrostClubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = FROST_CLUBBA_DROPS,
        .animations = FROST_CLUBBA_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FROST_CLUBBA_MACE_HITBOX(NPC_FrostClubba_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Clubba, "sam:white_clubba_1_mixed_0c", "sam_02b"),
    {}
};
