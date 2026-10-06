#include "mim_01.h"

#include "world/common/enemy/PiranhaPlant/idle.inc.c"

NpcData NpcData_PiranhaPlant[] = {
    {
        .id = NPC_PiranhaPlant,
        .pos = { 135.0f, 0.0f, -300.0f },
        .yaw = 0,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 135, 0, -300 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 400 },
            }
        },
        .settings = &NpcSettings_PiranhaPlant,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_Hitbox)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_PiranhaPlant, BTL_MIM_FORMATION_09, BTL_MIM_STAGE_00),
    {}
};
