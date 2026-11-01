#include "mim_01.h"

#include "world/common/enemy/PiranhaPlant/idle.inc.c"

NpcData NpcData_PiranhaPlant[] = {
    {
        .id = NPC_PiranhaPlant,
        .pos = $PiranhaPlant.pos,
        .yaw = $PiranhaPlant.yaw,
        .territory = $PiranhaPlant.territory,
        .settings = &NpcSettings_PiranhaPlant,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_Hitbox)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_PiranhaPlant, "mim:piranha_plant_2", "mim_01"),
    {}
};
