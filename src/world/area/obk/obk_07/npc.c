#include "obk_07.h"

#include "world/common/npc/Boo/idle.inc.c"

#include "../common/TrafficBoos.inc.c"

EvtScript EVS_NpcInit_TrafficBoo1 = {
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Y, 80)
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Z, -300)
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_TrafficBoo))
    Return
    End
};

NpcData NpcData_TrafficBoo1 = {
    .id = NPC_TrafficBoo1,
    .pos = { 523.0f, -139.0f, 193.0f },
    .yaw = 0,
    .init = &EVS_NpcInit_TrafficBoo1,
    .settings = &NpcSettings_Boo,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

EvtScript EVS_NpcInit_TrafficBoo2 = {
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Y, 80)
    Call(SetNpcVar, NPC_SELF, NPC_VAR_TRAFFIC_BOO_START_Z, -300)
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_TrafficBoo))
    Return
    End
};

NpcData NpcData_TrafficBoo2 = {
    .id = NPC_TrafficBoo2,
    .pos = { 473.0f, -122.0f, 247.0f },
    .yaw = 0,
    .init = &EVS_NpcInit_TrafficBoo2,
    .settings = &NpcSettings_Boo,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

EvtScript EVS_NpcInit_GuardBoo = {
    IfGe(GB_StoryProgress, STORY_CH3_GOT_WEIGHT)
        Set(MV_GuardDeparted, true)
        Call(RemoveNpc, NPC_SELF)
    Else
        ExecWait(EVS_SetupGuardBoo)
    EndIf
    Return
    End
};

NpcData NpcData_GuardBoo = {
    .id = NPC_GuardBoo,
    .pos = { 168.0f, 0.0f, -161.0f },
    .yaw = 270,
    .init = &EVS_NpcInit_GuardBoo,
    .settings = &NpcSettings_Boo,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
    .tattle = MSG_NpcTattle_OBK_GuardingChest,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_TrafficBoo1),
    NPC_GROUP(NpcData_TrafficBoo2),
    NPC_GROUP(NpcData_GuardBoo),
    {}
};
