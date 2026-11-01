#include "sbk_66.h"

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

NpcData NpcData_Bandit_03 = {
    .id = NPC_Bandit_03,
    .pos = $Bandit_03.pos,
    .yaw = $Bandit_03.yaw,
    .territory = $Bandit_03.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit_04 = {
    .id = NPC_Bandit_04,
    .pos = $Bandit_04.pos,
    .yaw = $Bandit_04.yaw,
    .territory = $Bandit_04.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit_05 = {
    .id = NPC_Bandit_05,
    .pos = $Bandit_05.pos,
    .yaw = $Bandit_05.yaw,
    .territory = $Bandit_05.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Bandit_06 = {
    .id = NPC_Bandit_06,
    .pos = $Bandit_06.pos,
    .yaw = $Bandit_06.yaw,
    .territory = $Bandit_06.territory,
    .settings = &NpcSettings_Bandit_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BANDIT_DROPS,
    .animations = BANDIT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Bandit_01, "sbk:bandit_1", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_02, "sbk:bandit_3", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_03, "sbk:bandit_4", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_04, "sbk:bandit_2", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_05, "sbk:bandit_2", "sbk_02"),
    NPC_GROUP(NpcData_Bandit_06, "sbk:bandit_2", "sbk_02"),
    {}
};
