#include "mim_06.h"

#include "world/common/enemy/PiranhaPlant/idle.inc.c"
#include "world/common/enemy/ForestFuzzy/wander.inc.c"

NpcData NpcData_PiranhaPlant_01[] = {
    {
        .id = NPC_PiranhaPlant_01,
        .pos = { -240.0f, 0.0f, -240.0f },
        .yaw = 0,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 400 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 400 },
            }
        },
        .settings = &NpcSettings_PiranhaPlant,
        .flags = 0,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_01_Hitbox)
};

NpcData NpcData_PiranhaPlant_02[] = {
    {
        .id = NPC_PiranhaPlant_02,
        .pos = { 240.0f, 0.0f, -240.0f },
        .yaw = 0,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 400 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 400 },
            }
        },
        .settings = &NpcSettings_PiranhaPlant,
        .flags = 0,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_02_Hitbox)
};

NpcData NpcData_Fuzzy = {
    .id = NPC_Fuzzy,
    .pos = { -140.0f, 0.0f, 300.0f },
    .yaw = 0,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 0, 0, 0 },
            .wanderSize = { 400 },
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
    NPC_GROUP(NpcData_PiranhaPlant_01, "mim:piranha_plant_2_forest_fuzzy_1", "mim_01"),
    NPC_GROUP(NpcData_PiranhaPlant_02, "mim:piranha_plant_1_forest_fuzzy_2", "mim_01"),
    NPC_GROUP(NpcData_Fuzzy, "mim:forest_fuzzy_1_mixed_07", "mim_01"),
    {}
};
