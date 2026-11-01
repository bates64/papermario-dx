#include "dgb_04.h"

#define AI_SENTINEL_FIRST_NPC NPC_Sentinel
#define AI_SENTINEL_LAST_NPC  NPC_Sentinel
#include "world/common/enemy/Sentinel/wander.inc.c"

NpcData NpcData_Sentinel = {
    .id = NPC_Sentinel,
    .pos = $Sentinel.pos,
    .yaw = $Sentinel.yaw,
    .territory = $Sentinel.territory,
    .settings = &NpcSettings_Sentinel_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = SENTINEL_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Sentinel),
    {}
};
