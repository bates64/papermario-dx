#include "sbk_26.h"

#include "world/common/enemy/Bandit/wander.inc.c"
#include "world/common/enemy/Pokey/wander.inc.c"

NpcData NpcData_Bandit = {
    .id = NPC_Bandit,
    .pos = $Bandit.pos,
    .yaw = $Bandit.yaw,
    .territory = $Bandit.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_FLYING,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey = {
    .id = NPC_Pokey,
    .pos = $Pokey.pos,
    .yaw = $Pokey.yaw,
    .territory = $Pokey.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Bandit, "sbk:bandit_4", "sbk_02"),
    NPC_GROUP(NpcData_Pokey, "sbk:pokey_2_bandit_2", "sbk_02"),
    {}
};
