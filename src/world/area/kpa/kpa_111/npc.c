#include "kpa_111.h"

#include "world/common/enemy/DryBones/wander.inc.c"

NpcData NpcData_DryBones[] = {
    {
        .id = NPC_DryBones_01,
        .pos = { -10.0f, 0.0f, 100.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -10, 0, 100 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { -10, 0, 100 },
                .detectSize = { 180 },
            }
        },
        .settings = &NpcSettings_DryBones_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = DRY_BONES_DROPS,
        .animations = DRY_BONES_ANIMS,
    },
    DRY_BONES_BONE_HITBOX(NPC_DryBones_01 + 1),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_01 + 2),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_01 + 3),
};

NpcData NpcData_DryBones_02[] = {
    {
        .id = NPC_DryBones_02,
        .pos = { 200.0f, 0.0f, 140.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 200, 0, 140 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 200, 0, 140 },
                .detectSize = { 180 },
            }
        },
        .settings = &NpcSettings_DryBones_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = DRY_BONES_DROPS,
        .animations = DRY_BONES_ANIMS,
    },
    DRY_BONES_BONE_HITBOX(NPC_DryBones_02 + 1),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_02 + 2),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_02 + 3),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_DryBones, "kpa:dry_bones_2", "kpa_13"),
    NPC_GROUP(NpcData_DryBones_02, "kpa:dry_bones_1_koopatrol_2", "kpa_13"),
    {}
};
