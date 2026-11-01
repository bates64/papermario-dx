#include "sbk_31.h"

#include "world/common/enemy/Bandit/wander.inc.c"

NpcData NpcData_Bandit = {
    .id = NPC_Bandit,
    .pos = $Bandit.pos,
    .yaw = $Bandit.yaw,
    .territory = $Bandit.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Bandit, "sbk:bandit_4", "sbk_02"),
    {}
};
