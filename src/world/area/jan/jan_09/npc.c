#include "jan_09.h"

#include "world/common/enemy/MBush/idle.inc.c"
#include "world/common/enemy/SpearGuy/wander.inc.c"

NpcData NpcData_SpearGuy[] = {
    {
        .id = NPC_SpearGuy,
        .pos = $SpearGuy.pos,
        .yaw = $SpearGuy.yaw,
        .territory = $SpearGuy.territory,
        .settings = &NpcSettings_SpearGuy_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = SPEAR_GUY_DROPS,
        .animations = SPEAR_GUY_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    SPEAR_GUY_HITBOX(NPC_SpearGuy_Hitbox)
};

NpcData NpcData_MBush_01 = {
    .id = NPC_MBush_01,
    .pos = $MBush_01.pos,
    .yaw = $MBush_01.yaw,
    .settings = &NpcSettings_MBush,
    .flags = MBUSH_FLAGS,
    .drops = MBUSH_DROPS,
    .animations = MBUSH_ANIMS,
    .tattle = MSG_NpcTattle_MBush,
};

NpcData NpcData_MBush_02 = {
    .id = NPC_MBush_02,
    .pos = $MBush_02.pos,
    .yaw = $MBush_02.yaw,
    .settings = &NpcSettings_MBush,
    .flags = MBUSH_FLAGS,
    .drops = MBUSH_DROPS,
    .animations = MBUSH_ANIMS,
    .tattle = MSG_NpcTattle_MBush,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpearGuy, "jan:spear_guy_1_jungle_fuzzy_3", "jan_01:b"),
    NPC_GROUP(NpcData_MBush_01, "jan:m_bush_2", "jan_01:b"),
    NPC_GROUP(NpcData_MBush_02, "jan:m_bush_2", "jan_01:b"),
    {}
};
