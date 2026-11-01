#include "sbk_42.h"

#include "world/common/enemy/Bandit/wander.inc.c"

NpcData NpcData_Bandit_01 = {
    .id = NPC_Bandit_01,
    .pos = $Bandit_01.pos,
    .yaw = $Bandit_01.yaw,
    .territory = $Bandit_01.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit_02 = {
    .id = NPC_Bandit_02,
    .pos = $Bandit_02.pos,
    .yaw = $Bandit_02.yaw,
    .territory = $Bandit_02.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Bandit_01, "sbk:bandit_2", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_02, "sbk:bandit_3", "sbk_02"),
    {}
};
