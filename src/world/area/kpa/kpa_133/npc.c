#include "kpa_133.h"

#include "world/common/npc/Toad/idle.inc.c"

EvtScript EVS_NpcInit_Toad = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_HAS_SHADOW, false)
    Return
    End
};

NpcData NpcData_Dummy = {
    .id = NPC_Dummy,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 0,
    .init = &EVS_NpcInit_Toad,
    .settings = &NpcSettings_Toad,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_HAS_NO_SPRITE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN,
    .drops = NO_DROPS,
    .animations = TOAD_RED_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Dummy),
    {}
};
