#include "mim_05.h"

#include "world/common/enemy/PiranhaPlant/idle.inc.c"

NpcData NpcData_PiranhaPlant_01[] = {
    {
        .id = NPC_PiranhaPlant_01,
        .pos = $PiranhaPlant_01.pos,
        .yaw = $PiranhaPlant_01.yaw,
        .territory = $PiranhaPlant_01.territory,
        .settings = &NpcSettings_PiranhaPlant,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
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
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = PIRANHA_PLANT_DROPS,
        .animations = PIRANHA_PLANT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    PIRANHA_PLANT_HITBOX(NPC_PiranhaPlant_02_Hitbox)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_PiranhaPlant_01, "mim:piranha_plant_4", "mim_01"),
    NPC_GROUP(NpcData_PiranhaPlant_02, "mim:piranha_plant_3", "mim_01"),
    {}
};
