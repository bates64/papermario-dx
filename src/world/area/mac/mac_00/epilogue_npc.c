#include "mac_00.h"

#include "world/common/npc/HarryT/idle.h"
#include "world/common/npc/TheMaster/idle.h"
#include "world/common/npc/VannaT/idle.h"
#include "world/common/npc/Chan/idle.h"
#include "world/common/npc/Lee/idle.h"
#include "world/common/npc/Quizmo/base.h"

EvtScript EVS_NpcInteract_Goompapa_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Goompapa_Talk, ANIM_Goompapa_Idle, 0, MSG_Outro_0024)
    Return
    End
};

EvtScript EVS_NpcInit_Goompapa_Epilogue = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Goompapa_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_Goomama_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Goomama_Talk, ANIM_Goomama_Idle, 0, MSG_Outro_0025)
    Return
    End
};

EvtScript EVS_NpcInit_Goomama_Epilogue = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Goomama_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_Gooma_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Gooma_Talk, ANIM_Gooma_Idle, 0, MSG_Outro_0026)
    Return
    End
};

EvtScript EVS_NpcInit_Gooma_Epilogue = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Gooma_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_ChuckQuizmo_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_ChuckQuizmo_Talk, ANIM_ChuckQuizmo_Idle, 0, MSG_Outro_0027)
    Return
    End
};

EvtScript EVS_NpcInit_ChuckQuizmo_Epilogue = {
    Call(SetNpcPos, NPC_ChuckQuizmo, 460, 20, -130)
    Call(SetNpcYaw, NPC_ChuckQuizmo, 90)
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_ChuckQuizmo_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_VannaT_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_VannaT_Wave, ANIM_VannaT_Wave, 0, MSG_Outro_003B)
    Return
    End
};

EvtScript EVS_NpcInit_VannaT_Epilogue = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_VannaT_Happy)
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_VannaT_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_Chan_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Chan_Run, ANIM_Chan_Idle, 0, MSG_Outro_0029)
    Return
    End
};

EvtScript EVS_NpcInit_Chan_Epilogue = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt, COLLIDER_FLAGS_UPPER_MASK)
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Chan_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_Lee_Epilogue = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Lee_Talk, ANIM_Lee_Idle, 0, MSG_Outro_002A)
    Return
    End
};

EvtScript EVS_NpcInit_Lee_Epilogue = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Lee_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_TheMaster_Epilogue = {
    Call(SpeakToPlayer, NPC_TheMaster, ANIM_TheMaster_Talk, ANIM_TheMaster_Idle, 0, MSG_Outro_0028)
    Return
    End
};

EvtScript EVS_NpcInit_TheMaster_Epilogue = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_TheMaster_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_Toad_01_Epilogue = {
    Call(SpeakToPlayer, NPC_Toad_01, ANIM_HarryT_Talk, ANIM_HarryT_Idle, 0, MSG_Outro_002B)
    Return
    End
};

EvtScript EVS_NpcInit_Toad_01_Epilogue = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_mono1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_mono2, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_mono3, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_mono4, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_mono5, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_mono6, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_dummy, COLLIDER_FLAGS_UPPER_MASK)
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Toad_01_Epilogue))
    Return
    End
};

EvtScript EVS_NpcInteract_HarryT_Epilogue = {
    Call(SpeakToPlayer, NPC_HarryT, ANIM_HarryT_Talk, ANIM_HarryT_Idle, 0, MSG_Outro_003A)
    Return
    End
};

EvtScript EVS_NpcInit_HarryT_Epilogue = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_HarryT_Epilogue))
    Return
    End
};

AnimID LimitAnims_Luigi[] = {
    ANIM_Luigi_Still,
    ANIM_Luigi_Idle,
    ANIM_Luigi_Walk,
    ANIM_Luigi_Run,
    ANIM_Luigi_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Luigi_Epilogue = {
    .id = NPC_Luigi_Epilogue,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 90,
    .settings = &NpcSettings_Dummy,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = LUIGI_ANIMS,
    .limitAnimations = LimitAnims_Luigi,
};

AnimID LimitAnims_Goompapa_Epilogue[] = {
    ANIM_Goompapa_Still,
    ANIM_Goompapa_Idle,
    ANIM_Goompapa_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Goomama_Epilogue[] = {
    ANIM_Goomama_Still,
    ANIM_Goomama_Idle,
    ANIM_Goomama_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Gooma_Epilogue[] = {
    ANIM_Gooma_Still,
    ANIM_Gooma_Idle,
    ANIM_Gooma_Talk,
    ANIM_LIST_END
};

NpcData NpcData_GoombaFamilypa_Epilogue[] = {
    {
        .id = NPC_Goompapa_Epilogue,
        .pos = { 70.0f, 0.0f, -30.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Goompapa_Epilogue,
        .settings = &NpcSettings_Goompapa,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = GOOMPAPA_ANIMS,
        .limitAnimations = LimitAnims_Goompapa_Epilogue,
        .tattle = MSG_NpcTattle_Goompapa,
    },
    {
        .id = NPC_Goomama_Epilogue,
        .pos = { 40.0f, 0.0f, 20.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Goomama_Epilogue,
        .settings = &NpcSettings_Goomama,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = GOOMAMA_ANIMS,
        .limitAnimations = LimitAnims_Goomama_Epilogue,
        .tattle = MSG_NpcTattle_Goomama,
    },
    {
        .id = NPC_Gooma_Epilogue,
        .pos = { 20.0f, 0.0f, -35.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Gooma_Epilogue,
        .settings = &NpcSettings_Gooma,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = GOOMA_ANIMS,
        .limitAnimations = LimitAnims_Gooma_Epilogue,
        .tattle = MSG_NpcTattle_Gooma,
    },
};

AnimID LimitAnims_Quizmo_Epilogue[] = {
    ANIM_ChuckQuizmo_Still,
    ANIM_ChuckQuizmo_Idle,
    ANIM_ChuckQuizmo_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_VannaT_Epilogue[] = {
    ANIM_VannaT_Still,
    ANIM_VannaT_Happy,
    ANIM_VannaT_Wave,
    ANIM_LIST_END
};

NpcData NpcData_ChuckQuizmo_Epilogue[] = {
    {
        .id = NPC_ChuckQuizmo,
        .pos = { 545.0f, 20.0f, 150.0f },
        .yaw = 30,
        .init = &EVS_NpcInit_ChuckQuizmo_Epilogue,
        .settings = &NpcSettings_Dummy,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = QUIZMO_ANIMS,
        .limitAnimations = LimitAnims_Quizmo_Epilogue,
        .tattle = MSG_NpcTattle_ChuckQuizmo,
    },
    {
        .id = NPC_VannaT_Epilogue,
        .pos = { 500.0f, 20.0f, -130.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_VannaT_Epilogue,
        .settings = &NpcSettings_VannaT,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = VANNA_T_ANIMS,
        .limitAnimations = LimitAnims_VannaT_Epilogue,
        .tattle = MSG_NpcTattle_MAC00_ShopOwner,
    },
};

AnimID LimitAnims_TheMaster_Epilogue[] = {
    ANIM_TheMaster_Still,
    ANIM_TheMaster_Idle,
    ANIM_TheMaster_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Chan_Epilogue[] = {
    ANIM_Chan_Still,
    ANIM_Chan_Idle,
    ANIM_Chan_Run,
    ANIM_LIST_END
};

AnimID LimitAnims_Lee_Epilogue[] = {
    ANIM_Lee_Still,
    ANIM_Lee_Idle,
    ANIM_Lee_Talk,
    ANIM_LIST_END
};

NpcData NpcData_DojoMembers_Epilogue[] = {
    {
        .id = NPC_TheMaster,
        .pos = { 375.0f, 115.0f, -440.0f },
        .yaw = 225,
        .init = &EVS_NpcInit_TheMaster_Epilogue,
        .settings = &NpcSettings_TheMaster,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = THE_MASTER_ANIMS,
        .limitAnimations = LimitAnims_TheMaster_Epilogue,
        .tattle = MSG_NpcTattle_TheMaster,
    },
    {
        .id = NPC_Chan,
        .pos = { 310.0f, 115.0f, -390.0f },
        .yaw = 45,
        .init = &EVS_NpcInit_Chan_Epilogue,
        .settings = &NpcSettings_Chan,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = CHAN_ANIMS,
        .limitAnimations = LimitAnims_Chan_Epilogue,
        .tattle = MSG_NpcTattle_Chan,
    },
    {
        .id = NPC_Lee,
        .pos = { 330.0f, 115.0f, -410.0f },
        .yaw = 45,
        .init = &EVS_NpcInit_Lee_Epilogue,
        .settings = &NpcSettings_Lee,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = LEE_ANIMS,
        .limitAnimations = LimitAnims_Lee_Epilogue,
        .tattle = MSG_NpcTattle_Lee,
    },
};

AnimID LimitAnims_HarryT_Epilogue[] = {
    ANIM_HarryT_Still,
    ANIM_HarryT_Idle,
    ANIM_HarryT_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Toad_01_Epilogue[] = {
    {
        .id = NPC_Toad_01,
        .pos = { 430.0f, 20.0f, -373.0f },
        .yaw = 223,
        .init = &EVS_NpcInit_Toad_01_Epilogue,
        .settings = &NpcSettings_HarryT,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = HARRY_T_ANIMS,
        .limitAnimations = LimitAnims_HarryT_Epilogue,
        .tattle = MSG_NpcTattle_MAC00_ShopOwner,
    },
    {
        .id = NPC_HarryT,
        .pos = { 410.0f, 20.0f, -320.0f },
        .yaw = 43,
        .init = &EVS_NpcInit_HarryT_Epilogue,
        .settings = &NpcSettings_HarryT,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = HARRY_T_ANIMS,
        .limitAnimations = LimitAnims_HarryT_Epilogue,
        .tattle = MSG_NpcTattle_MAC00_ShopOwner,
    },
};

extern NpcData NpcData_SharedTownsfolk[9]; //@bug this NPC list actually has 10 NPCs in it...
extern NpcData NpcData_Waterfront_Family[4];

NpcGroupList EpilogueNPCs = {
    NPC_GROUP(NpcData_Luigi_Epilogue),
    NPC_GROUP(NpcData_DojoMembers_Epilogue),
    NPC_GROUP(NpcData_GoombaFamilypa_Epilogue),
    NPC_GROUP(NpcData_ChuckQuizmo_Epilogue),
    NPC_GROUP(NpcData_Toad_01_Epilogue),
    NPC_GROUP(NpcData_SharedTownsfolk),
    NPC_GROUP(NpcData_Waterfront_Family),
    {}
};
