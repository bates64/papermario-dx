#include "mim_09.h"

#include "world/common/npc/Oaklie/idle.inc.c"
#include "world/common/enemy/ForestFuzzy/wander.inc.c"

NpcData NpcData_Fuzzy = {
    .id = NPC_Fuzzy,
    .pos = { 270.0f, 0.0f, 200.0f },
    .yaw = 0,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 270, 0, 200 },
            .wanderSize = { 100 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 0, 0, 0 },
            .detectSize = { 400 },
        }
    },
    .settings = &NpcSettings_ForestFuzzy_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = FOREST_FUZZY_DROPS,
    .animations = FOREST_FUZZY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Fuzzy, BTL_MIM_FORMATION_05, BTL_MIM_STAGE_00),
    {}
};
