#include "jan_12.h"

#include "world/common/enemy/SpearGuy/wander.inc.c"

NpcData NpcData_SpearGuy[] = {
    {
        .id = NPC_SpearGuy,
        .pos = $SpearGuy.pos,
        .yaw = $SpearGuy.yaw,
        .territory = $SpearGuy.territory,
        .settings = &NpcSettings_SpearGuy_Wander,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = SPEAR_GUY_DROPS,
        .animations = SPEAR_GUY_ANIMS,
    },
    SPEAR_GUY_HITBOX(NPC_SpearGuy_Hitbox)
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpearGuy, "jan:spear_guy_1_jungle_fuzzy_1_spear_guy_1_jungle_fuzzy_1", "jan_04"),
    {}
};
