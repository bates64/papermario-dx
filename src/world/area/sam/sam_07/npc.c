#include "sam_07.h"

#include "world/common/enemy/Gulpit/wander.inc.c"
#include "world/common/enemy/FrostPiranha/idle.inc.c"

NpcData NpcData_Gulpit[] = {
    {
        .id = NPC_Gulpit,
        .pos = $Gulpit.pos,
        .yaw = $Gulpit.yaw,
        .territory = $Gulpit.territory,
        .settings = &NpcSettings_Gulpit_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = GULPIT_DROPS,
        .animations = GULPIT_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    GULPIT_HITBOX(NPC_Gulpit_Hitbox),
};

NpcData NpcData_FrostPiranha_01[] = {
    {
        .id = NPC_FrostPiranha_01,
        .pos = $FrostPiranha_01.pos,
        .yaw = $FrostPiranha_01.yaw,
        .territory = $FrostPiranha_01.territory,
        .settings = &NpcSettings_FrostPiranha,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = FROST_PIRANHA_DROPS,
        .animations = FROST_PIRANHA_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FROST_PIRANHA_HITBOX(NPC_FrostPiranha_01_Hitbox),
};

NpcData NpcData_FrostPiranha_02[] = {
    {
        .id = NPC_FrostPiranha_02,
        .pos = $FrostPiranha_02.pos,
        .yaw = $FrostPiranha_02.yaw,
        .territory = $FrostPiranha_02.territory,
        .settings = &NpcSettings_FrostPiranha,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = FROST_PIRANHA_DROPS,
        .animations = FROST_PIRANHA_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    FROST_PIRANHA_HITBOX(NPC_FrostPiranha_02_Hitbox),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Gulpit, "sam:gulpit_2_frost_piranha_1", "sam_02:b"),
    NPC_GROUP(NpcData_FrostPiranha_01, "sam:frost_piranha_1_gulpit_1_frost_piranha_1", "sam_02:b"),
    NPC_GROUP(NpcData_FrostPiranha_02, "sam:frost_piranha_4", "sam_02:b"),
    {}
};
