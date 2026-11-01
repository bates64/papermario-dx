#include "sam_03.h"

#include "world/common/enemy/Gulpit/wander.inc.c"

NpcData NpcData_Gulpit_01[] = {
    {
        .id = NPC_Gulpit_01,
        .pos = $Gulpit_01.pos,
        .yaw = $Gulpit_01.yaw,
        .territory = $Gulpit_01.territory,
        .settings = &NpcSettings_Gulpit_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = GULPIT_DROPS,
        .animations = GULPIT_ANIMS,
        .limitAnimations = LimitAnims_Gulpit,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    GULPIT_HITBOX(NPC_Gulpit_01_Hitbox),
};

NpcData NpcData_Gulpit_02[] = {
    {
        .id = NPC_Gulpit_02,
        .pos = $Gulpit_02.pos,
        .yaw = $Gulpit_02.yaw,
        .territory = $Gulpit_02.territory,
        .settings = &NpcSettings_Gulpit_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = GULPIT_DROPS,
        .animations = GULPIT_ANIMS,
        .limitAnimations = LimitAnims_Gulpit,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    GULPIT_HITBOX(NPC_Gulpit_02_Hitbox),
};

NpcGroupList AfterNPCs = {
    NPC_GROUP(NpcData_Gulpit_01, "sam:gulpit_2", "sam_01"),
    NPC_GROUP(NpcData_Gulpit_02, "sam:gulpit_3", "sam_01"),
    {}
};
