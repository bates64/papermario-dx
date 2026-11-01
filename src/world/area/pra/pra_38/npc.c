#include "pra_38.h"

#include "world/common/enemy/Swooper/wander.inc.c"

EvtScript EVS_NpcInit_Swoopula = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_REFLECT_FLOOR, true)
    Return
    End
};

NpcData NpcData_Swoopula_01 = {
    .id = NPC_Swoopula_01,
    .pos = $Swoopula_01.pos,
    .yaw = $Swoopula_01.yaw,
    .territory = $Swoopula_01.territory,
    .init = &EVS_NpcInit_Swoopula,
    .settings = &NpcSettings_Swoopula_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = SWOOPULA_DROPS,
    .animations = SWOOPULA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Swoopula_02 = {
    .id = NPC_Swoopula_02,
    .pos = $Swoopula_02.pos,
    .yaw = $Swoopula_02.yaw,
    .territory = $Swoopula_02.territory,
    .init = &EVS_NpcInit_Swoopula,
    .settings = &NpcSettings_Swoopula_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = SWOOPULA_DROPS,
    .animations = SWOOPULA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Swoopula_01, "pra:swoopula_3", "pra_01"),
    NPC_GROUP(NpcData_Swoopula_02, "pra:swoopula_4", "pra_01"),
    {}
};
