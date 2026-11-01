#include "kpa_01.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BonyBeetle_01 = {
    .id = NPC_BonyBeetle_01,
    .pos = $BonyBeetle_01.pos,
    .yaw = $BonyBeetle_01.yaw,
    .territory = $BonyBeetle_01.territory,
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS,
    .animations = BONY_BEETLE_ANIMS,
};

NpcData NpcData_BonyBeetle_02 = {
    .id = NPC_BonyBeetle_02,
    .pos = $BonyBeetle_02.pos,
    .yaw = $BonyBeetle_02.yaw,
    .territory = $BonyBeetle_02.territory,
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS,
    .animations = BONY_BEETLE_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BonyBeetle_01, "kpa:bony_beetle_2", "kpa_03"),
    NPC_GROUP(NpcData_BonyBeetle_02, "kpa:bony_beetle_3", "kpa_03"),
    {}
};
