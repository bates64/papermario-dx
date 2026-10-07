#include "kpa_102.h"

#include "world/common/enemy/HammerBros/wander.inc.c"
#include "world/common/enemy/Koopatrol/wander.inc.c"
#include "world/common/enemy/FlyingMagikoopa/wander.inc.c"

NpcData NpcData_Koopatrol = {
    .id = NPC_Koopatrol,
    .pos = { -200.0f, 0.0f, -225.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { -200, 0, -225 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { -200, 0, -225 },
            .detectSize = { 200 },
        }
    },
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
};

NpcData NpcData_FlyingMagikoopa[] = {
    {
        .id = NPC_FlyingMagikoopa,
        .pos = { 125.0f, 50.0f, -225.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_RECT,
                .centerPos  = { 125, 50, -225 },
                .wanderSize = { 120, 25 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 125, 50, -225 },
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
    FLYING_MAGIKOOPA_SPELL_HITBOX(NPC_FlyingMagikoopa + 1),
};

NpcData NpcData_HammerBros[] = {
    {
        .id = NPC_HammerBros,
        .pos = { 450.0f, 0.0f, -225.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 450, 0, -225 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 450, 0, -225 },
                .detectSize = { 200 },
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
    NPC_GROUP(NpcData_Koopatrol, "kpa:koopatrol_2_magikoopa_1_flying_magikoopa_1", "kpa_09"),
    NPC_GROUP(NpcData_FlyingMagikoopa, "kpa:flying_magikoopa_1_mixed_32", "kpa_09"),
    NPC_GROUP(NpcData_HammerBros, "kpa:hammer_bro_3_flying_magikoopa_1", "kpa_09"),
    {}
};
