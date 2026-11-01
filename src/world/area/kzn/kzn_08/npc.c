#include "kzn_08.h"

#include "world/common/enemy/LavaBubble/wander.inc.c"
#include "world/common/enemy/PutridPiranha/idle.inc.c"

NpcData NpcData_PutridPiranha[] = {
    {
        .id = NPC_PutridPiranha,
        .pos = $PutridPiranha.pos,
        .yaw = $PutridPiranha.yaw,
        .territory = $PutridPiranha.territory,
        .settings = &NpcSettings_PutridPiranha,
        .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = PUTRID_PIRANHA_DROPS,
        .animations = PUTRID_PIRANHA_ANIMS,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    PUTRID_PIRANHA_HITBOX(NPC_Piranha_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_PutridPiranha, "kzn:putrid_piranha_1_lava_bubble_1_putrid_piranha_1", "kzn_04:b"),
    {}
};
