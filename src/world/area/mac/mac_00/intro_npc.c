#include "mac_00.h"

#include "world/common/npc/Chan/idle.h"
#include "world/common/npc/Lee/idle.h"

EvtScript EVS_NpcInit_Chan_Intro = {
    Call(SetNpcPos, NPC_SELF, 570, 20, -150)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

EvtScript EVS_NpcInit_Lee_Intro = {
    Call(SetNpcPos, NPC_SELF, 600, 20, -145)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

AnimID LimitAnims_Chan_Intro[] = {
    ANIM_Chan_Still,
    ANIM_Chan_Idle,
    ANIM_Chan_Run,
    ANIM_LIST_END
};

AnimID LimitAnims_Lee_Intro[] = {
    ANIM_Lee_Still,
    ANIM_Lee_Idle,
    ANIM_Lee_Talk,
    ANIM_LIST_END
};

NpcData NpcData_IntroNPCs[] = {
    {
        .id = NPC_Luigi_Intro,
        .pos = $Luigi_Intro.pos,
        .yaw = $Luigi_Intro.yaw,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = LUIGI_ANIMS,
    },
    {
        .id = NPC_Toad_01,
        .pos = $Toad_01_1.pos,
        .yaw = $Toad_01_1.yaw,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_GateGuardian,
    },
    {
        .id = NPC_Toad_02,
        .pos = $Toad_02.pos,
        .yaw = $Toad_02.yaw,
        .territory = $Toad_02.territory,
        .settings = &NpcSettings_Toad_Wander,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ShopLoiterer,
    },
    {
        .id = NPC_Toad_03,
        .pos = $Toad_03.pos,
        .yaw = $Toad_03.yaw,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_DojoSpectator,
    },
    {
        .id = NPC_Chan,
        .pos = $Chan_1.pos,
        .yaw = $Chan_1.yaw,
        .init = &EVS_NpcInit_Chan_Intro,
        .settings = &NpcSettings_Chan,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = CHAN_ANIMS,
        .limitAnimations = LimitAnims_Chan_Intro,
        .tattle = MSG_NpcTattle_Chan,
    },
    {
        .id = NPC_Lee,
        .pos = $Lee_1.pos,
        .yaw = $Lee_1.yaw,
        .init = &EVS_NpcInit_Lee_Intro,
        .settings = &NpcSettings_Lee,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = LEE_ANIMS,
        .limitAnimations = LimitAnims_Lee_Intro,
        .tattle = MSG_NpcTattle_Lee,
    },
};

NpcGroupList IntroNPCs = {
    NPC_GROUP(NpcData_IntroNPCs),
    {}
};
