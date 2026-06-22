#include "obk_05.h"

#include "world/common/npc/Boo/idle.inc.c"

#include "../common/TrafficBoos.inc.c"

EvtScript N(EVS_NpcInit_TrafficBoo1) = {
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Y, 40)
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Z, -430)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_TrafficBoo)))
    Return
    End
};

EvtScript N(EVS_NpcInit_TrafficBoo2) = {
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Y, 40)
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Z, -430)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_TrafficBoo)))
    Return
    End
};

NpcData N(NpcData_Boo_01)[] = {
    {
        .id = NPC_Boo_01,
        .pos = { 523.0f, -139.0f, 193.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_TrafficBoo1),
        .settings = &N(NpcSettings_Boo),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
    {
        .id = NPC_Boo_02,
        .pos = { 473.0f, -122.0f, 247.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_TrafficBoo2),
        .settings = &N(NpcSettings_Boo),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Boo_01)),
    {}
};
