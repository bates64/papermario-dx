#include "sbk_05.h"

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

NpcData NpcData_Pokey_03 = {
    .id = NPC_Pokey_03,
    .pos = $Pokey_03.pos,
    .yaw = $Pokey_03.yaw,
    .territory = $Pokey_03.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_04 = {
    .id = NPC_Pokey_04,
    .pos = $Pokey_04.pos,
    .yaw = $Pokey_04.yaw,
    .territory = $Pokey_04.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_05 = {
    .id = NPC_Pokey_05,
    .pos = $Pokey_05.pos,
    .yaw = $Pokey_05.yaw,
    .territory = $Pokey_05.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_06 = {
    .id = NPC_Pokey_06,
    .pos = $Pokey_06.pos,
    .yaw = $Pokey_06.yaw,
    .territory = $Pokey_06.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_07 = {
    .id = NPC_Pokey_07,
    .pos = $Pokey_07.pos,
    .yaw = $Pokey_07.yaw,
    .territory = $Pokey_07.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_08 = {
    .id = NPC_Pokey_08,
    .pos = $Pokey_08.pos,
    .yaw = $Pokey_08.yaw,
    .territory = $Pokey_08.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_09 = {
    .id = NPC_Pokey_09,
    .pos = $Pokey_09.pos,
    .yaw = $Pokey_09.yaw,
    .territory = $Pokey_09.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Pokey_10 = {
    .id = NPC_Pokey_10,
    .pos = $Pokey_10.pos,
    .yaw = $Pokey_10.yaw,
    .territory = $Pokey_10.territory,
    .settings = &NpcSettings_Pokey_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = POKEY_DROPS,
    .animations = POKEY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Pokey_01, "sbk:pokey_1", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_02, "sbk:pokey_1", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_03, "sbk:pokey_1", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_04, "sbk:pokey_3", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_05, "sbk:pokey_3", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_06, "sbk:pokey_4", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_07, "sbk:pokey_2", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_08, "sbk:pokey_2", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_09, "sbk:pokey_2", "sbk_02"),
    NPC_GROUP(NpcData_Pokey_10, "sbk:pokey_2", "sbk_02"),
    {}
};
