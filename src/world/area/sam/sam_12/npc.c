#include "sam_12.h"

#include "world/common/npc/Merlar/idle.inc.c"

EvtScript EVS_NpcInit_Merlar = {
    Call(BindNpcAux, NPC_SELF, Ref(EVS_NpcAux_Merlar_Idle))
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Merlar_Idle))
    Call(EnableNpcShadow, NPC_SELF, false)
    Return
    End
};

NpcData NpcData_Merlar = {
    .id = NPC_Merlar,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 180,
    .init = &EVS_NpcInit_Merlar,
    .settings = &NpcSettings_Merlar,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = NO_DROPS,
    .animations = MERLAR_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Merlar),
    {}
};
