#include "kkj_02.h"

#include "world/common/npc/ToadGuard/idle.inc.c"
#include "world/common/npc/Toad/wander.inc.c"
#include "world/common/npc/Toad/idle.inc.c"

EvtScript EVS_NpcInteract_Toad = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Intro_0049)
    Return
    End
};

EvtScript EVS_NpcInteract_ToadGuard = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_ToadGuard_Red_Talk, ANIM_ToadGuard_Red_Idle, 0, MSG_Intro_004A)
    Return
    End
};

EvtScript EVS_NpcInit_Toad = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toad)
    Return
    End
};

EvtScript EVS_NpcInit_ToadGuard = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_ToadGuard)
    Return
    End
};

NpcData NpcData_Toads[] = {
    {
        .id = NPC_Toad,
        .pos = $Toad.pos,
        .yaw = $Toad.yaw,
        .territory = $Toad.territory,
        .init = &EVS_NpcInit_Toad,
        .settings = &NpcSettings_Toad_Wander,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
    },
    {
        .id = NPC_ToadGuard,
        .pos = $ToadGuard.pos,
        .yaw = $ToadGuard.yaw,
        .init = &EVS_NpcInit_ToadGuard,
        .settings = &NpcSettings_ToadGuard,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Toads),
    {}
};
