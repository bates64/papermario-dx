#include "mim_06.h"

#include "world/common/enemy/PiranhaPlant/idle.inc.c"
#include "world/common/enemy/ForestFuzzy/wander.inc.c"

NpcData NpcData_PiranhaPlant_01[] = {
    {
        .id = NPC_PiranhaPlant_01,
        .pos = $PiranhaPlant_01.pos,
        .yaw = $PiranhaPlant_01.yaw,
        .territory = $PiranhaPlant_01.territory,
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
        .pos = $PiranhaPlant_02.pos,
        .yaw = $PiranhaPlant_02.yaw,
        .territory = $PiranhaPlant_02.territory,
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
    .pos = $Fuzzy.pos,
    .yaw = $Fuzzy.yaw,
    .territory = $Fuzzy.territory,
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
