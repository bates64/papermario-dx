#include "pra_36.h"

#include "world/common/enemy/Duplighost/wander.inc.c"

EvtScript EVS_NpcInit_Duplighost = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_REFLECT_FLOOR, true)
    Return
    End
};

NpcData NpcData_Duplighost = {
    .id = NPC_Duplighost,
    .pos = $Duplighost.pos,
    .yaw = $Duplighost.yaw,
    .territory = $Duplighost.territory,
    .init = &EVS_NpcInit_Duplighost,
    .settings = &NpcSettings_Duplighost_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = DUPLIGHOST_DROPS,
    .animations = DUPLIGHOST_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Duplighost, "pra3:duplighost_2_gray_magikoopa_1_red_magikoopa_1", "pra_01"),
    {}
};
