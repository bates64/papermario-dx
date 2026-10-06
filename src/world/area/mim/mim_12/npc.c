#include "mim_12.h"

#include "world/common/npc/Boo/idle.inc.c"

EvtScript EVS_NpcInit_GateBoo_01 = {
    Return
    End
};

EvtScript EVS_NpcInit_GateBoo_02 = {
    Return
    End
};

NpcData NpcData_GateBoos[] = {
    {
        .id = NPC_GateBoo_01,
        .pos = { -68.0f, 65.0f, -56.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_GateBoo_01,
        .settings = &NpcSettings_Boo,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
    {
        .id = NPC_GateBoo_02,
        .pos = { -125.0f, 65.0f, 60.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_GateBoo_02,
        .settings = &NpcSettings_Boo,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_GateBoos),
    {}
};
