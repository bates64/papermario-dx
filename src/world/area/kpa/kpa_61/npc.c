#include "kpa_61.h"

#include "world/common/enemy/Koopatrol/wander.inc.c"
#include "world/common/enemy/FlyingMagikoopa/wander.inc.c"

NpcData NpcData_Koopatrol_01 = {
    .id = NPC_Koopatrol_01,
    .pos = { 300.0f, -160.0f, 140.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 300, -160, 140 },
            .wanderSize = { 50 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 300, -160, 140 },
            .detectSize = { 200 },
        }
    },
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_Koopatrol_02 = {
    .id = NPC_Koopatrol_02,
    .pos = { 850.0f, -160.0f, 390.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = false,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 850, -160, 390 },
            .wanderSize = { 50 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 850, -160, 390 },
            .detectSize = { 200 },
        }
    },
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_FlyingMagikoopa_01[] = {
    {
        .id = NPC_FlyingMagikoopa_01,
        .pos = { 500.0f, 250.0f, -50.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_RECT,
                .centerPos  = { 500, 250, -50 },
                .wanderSize = { 120, 25 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 500, 250, -50 },
                .detectSize = { 200 },
            }
        },
        .settings = &NpcSettings_FlyingMagikoopa_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = FLYING_MAGIKOOPA_DROPS,
        .animations = FLYING_MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_FlyingMagikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FLYING_MAGIKOOPA_SPELL_HITBOX(NPC_FlyingMagikoopa_01_Spell),
};

NpcData NpcData_FlyingMagikoopa_02[] = {
    {
        .id = NPC_FlyingMagikoopa_02,
        .pos = { 200.0f, 250.0f, -50.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_RECT,
                .centerPos  = { 200, 250, -50 },
                .wanderSize = { 120, 25 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 200, 250, -50 },
                .detectSize = { 200 },
            }
        },
        .settings = &NpcSettings_FlyingMagikoopa_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = FLYING_MAGIKOOPA_DROPS,
        .animations = FLYING_MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_FlyingMagikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FLYING_MAGIKOOPA_SPELL_HITBOX(NPC_FlyingMagikoopa_02_Spell),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Koopatrol_01, "kpa:koopatrol_1_dry_bones_2", "kpa_07"),
    NPC_GROUP(NpcData_Koopatrol_02, "kpa:koopatrol_1_bony_beetle_2", "kpa_07"),
    NPC_GROUP(NpcData_FlyingMagikoopa_01, "kpa:flying_magikoopa_1_dry_bones_2", "kpa_07"),
    NPC_GROUP(NpcData_FlyingMagikoopa_02, "kpa:flying_magikoopa_1_koopatrol_2", "kpa_07"),
    {}
};
