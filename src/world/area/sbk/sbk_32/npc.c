#include "sbk_32.h"

#include "world/common/enemy/Bandit/wander.inc.c"
#include "world/common/enemy/Pokey/wander.inc.c"

NpcData NpcData_Pokey_01 = {
    .id = NPC_Pokey_01,
    .pos = $Pokey_01.pos,
    .yaw = $Pokey_01.yaw,
    .territory = $Pokey_01.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_02 = {
    .id = NPC_Pokey_02,
    .pos = $Pokey_02.pos,
    .yaw = $Pokey_02.yaw,
    .territory = $Pokey_02.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

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
    NPC_GROUP(NpcData_Pokey_01, "sbk:pokey_2", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_02, "sbk:pokey_3", "sbk_02"),
    NPC_GROUP(NpcData_Bandit, "sbk:bandit_3", "sbk_02"),
    {}
};
