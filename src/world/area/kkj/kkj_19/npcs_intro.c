#include "kkj_19.h"

#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/TayceT/idle.inc.c"

EvtScript EVS_NpcInteract_TayceT = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_TayceT_Talk, ANIM_TayceT_Idle, 0, MSG_Intro_0031)
    Return
    End
};

EvtScript EVS_NpcInteract_Toad = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_Intro_0032)
    Return
    End
};

EvtScript EVS_NpcInit_TayceT = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_TayceT_Idle)
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_TayceT)
    Return
    End
};

EvtScript EVS_NpcInit_Toad = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toad)
    Return
    End
};

NpcData NpcData_TayceT[] = {
    {
        .id = NPC_TayceT,
        .pos = $TayceT.pos,
        .yaw = $TayceT.yaw,
        .init = &EVS_NpcInit_TayceT,
        .settings = &NpcSettings_TayceT,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TAYCE_T_ANIMS,
    },
    {
        .id = NPC_Toad,
        .pos = $Toad.pos,
        .yaw = $Toad.yaw,
        .init = &EVS_NpcInit_Toad,
        .settings = &NpcSettings_Toad,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
    },
};

NpcGroupList IntroNPCs = {
    NPC_GROUP(NpcData_TayceT),
    {}
};
