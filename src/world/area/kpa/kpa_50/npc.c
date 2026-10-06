#include "kpa_50.h"

#include "world/common/enemy/HammerBros/wander.inc.c"
#include "world/common/enemy/Koopatrol/wander.inc.c"

NpcData NpcData_Koopatrol_01 = {
    .id = NPC_Koopatrol_01,
    .pos = { -251.0f, 0.0f, -30.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -251, 0, -30 },
            .wanderSize = { 50 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -251, 0, -30 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_Koopatrol_02 = {
    .id = NPC_Koopatrol_02,
    .pos = { 100.0f, 0.0f, -30.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 100, 0, -30 },
            .wanderSize = { 50 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 100, 0, -30 },
            .detectSize = { 300 },
        }
    },
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_HammerBros_01[] = {
    {
        .id = NPC_HammerBros,
        .pos = { 450.0f, 0.0f, -30.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = false,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 450, 0, -30 },
                .wanderSize = { 50 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 450, 0, -30 },
                .detectSize = { 300 },
            }
        },
        .settings = &NpcSettings_HammerBros_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = HAMMER_BROS_DROPS,
        .animations = HAMMER_BROS_ANIMS,
    },
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 1),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 2),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 3),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 4),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 5),
    HAMMER_BROS_HAMMER_HITBOX(NPC_HammerBros + 6),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Koopatrol_01, "kpa:koopatrol_2", "kpa_01"),
    NPC_GROUP(NpcData_Koopatrol_02, "kpa:koopatrol_4", "kpa_01"),
    NPC_GROUP(NpcData_HammerBros_01, "kpa:hammer_bro_2", "kpa_01"),
    {}
};
