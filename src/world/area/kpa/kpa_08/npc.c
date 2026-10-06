#include "kpa_08.h"

#include "world/common/enemy/Magikoopa/wander.inc.c"

NpcData NpcData_Magikoopa[] = {
    {
        .id = NPC_Magikoopa,
        .pos = { -210.0f, 0.0f, 25.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_RECT,
                .centerPos  = { -210, 0, 25 },
                .wanderSize = { 30, 10 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { -210, 0, 25 },
                .detectSize = { 200 },
            }
        },
        .settings = &NpcSettings_Magikoopa_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = MAGIKOOPA_DROPS,
        .animations = MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_Magikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    MAGIKOOPA_SPELL_HITBOX(NPC_Magikoopa_Spell)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Magikoopa, "kpa:magikoopa_2_dry_bones_1", "kpa_01b"),
    {}
};
