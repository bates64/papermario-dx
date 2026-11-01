#include "kpa_113.h"

#include "world/common/enemy/SpikeTop/wander.inc.c"

NpcData NpcData_BonyBeetle = {
    .id = NPC_BonyBeetle,
    .pos = $BonyBeetle.pos,
    .yaw = $BonyBeetle.yaw,
    .territory = $BonyBeetle.territory,
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS,
    .animations = BONY_BEETLE_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_BonyBeetle, "kpa:bony_beetle_1_dry_bones_1_bony_beetle_1_magikoopa_1", "kpa_13"),
    {}
};
