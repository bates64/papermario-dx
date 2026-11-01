#include "obk_02.h"

#include "world/common/npc/Boo/idle.inc.c"

#include "../common/TrafficBoos.inc.c"

EvtScript EVS_NpcInit_TrafficBoo1 = {
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Y, 80)
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Z, -300)
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_TrafficBoo)
    Return
    End
};

EvtScript EVS_NpcInit_TrafficBoo2 = {
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Y, 80)
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Z, -300)
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_TrafficBoo)
    Return
    End
};

NpcData NpcData_TrafficBoos[] = {
    {
        .id = NPC_TrafficBoo1,
        .pos = $TrafficBoo1.pos,
        .yaw = $TrafficBoo1.yaw,
        .init = &EVS_NpcInit_TrafficBoo1,
        .settings = &NpcSettings_Boo,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
    {
        .id = NPC_TrafficBoo2,
        .pos = $TrafficBoo2.pos,
        .yaw = $TrafficBoo2.yaw,
        .init = &EVS_NpcInit_TrafficBoo2,
        .settings = &NpcSettings_Boo,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_TrafficBoos),
    {}
};
