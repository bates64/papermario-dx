#include "mim_09.h"

#include "world/common/npc/Oaklie/idle.inc.c"
#include "world/common/enemy/ForestFuzzy/wander.inc.c"

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
    NPC_GROUP(NpcData_Fuzzy, "mim:forest_fuzzy_2_piranha_plant_2", "mim_01"),
    {}
};
