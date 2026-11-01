#include "pra_04.h"

#include "world/common/enemy/Swooper/wander.inc.c"

NpcData NpcData_Swoopula = {
    .id = NPC_Swoopula,
    .pos = $Swoopula.pos,
    .yaw = $Swoopula.yaw,
    .territory = $Swoopula.territory,
    .settings = &NpcSettings_Swoopula_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = SWOOPULA_DROPS,
    .animations = SWOOPULA_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Swoopula, "pra3:swoopula_2_duplighost_1", "pra_01"),
    {}
};
