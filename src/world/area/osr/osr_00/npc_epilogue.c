#include "osr_00.h"

#include "world/common/npc/ToadGuard/idle.inc.c"
#include "world/common/npc/Yoshi/idle.inc.c"
#include "world/common/npc/YoshiKid/idle.inc.c"
#include "world/common/npc/Penguin/idle.inc.c"
#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/Boo/idle.inc.c"
#include "world/common/npc/Mouser/idle.inc.c"

EvtScript EVS_NpcInteract_LeaderYoshi = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_VillageLeader_Talk, ANIM_VillageLeader_Idle, 0, MSG_Outro_0055)
    Return
    End
};

EvtScript EVS_NpcInit_LeaderYoshi = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_LeaderYoshi))
    Return
    End
};

EvtScript EVS_NpcInteract_Yoshi = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Yoshi_Green_Talk, ANIM_Yoshi_Green_Idle, 0, MSG_Outro_0060)
    Return
    End
};

EvtScript EVS_NpcInit_Yoshi = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Yoshi))
    Return
    End
};

EvtScript EVS_NpcInteract_YoshiKid = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_YoshiKid_Green_Talk, ANIM_YoshiKid_Green_Idle, 0, MSG_Outro_0061)
    Return
    End
};

EvtScript EVS_NpcInit_YoshiKid = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_YoshiKid))
    Return
    End
};

EvtScript EVS_NpcInteract_MayorPenguin = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_MayorPenguin_Talk, ANIM_MayorPenguin_Idle, 0, MSG_Outro_0056)
    Return
    End
};

EvtScript EVS_NpcInit_MayorPenguin = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_MayorPenguin))
    Return
    End
};

EvtScript EVS_NpcInteract_MayorPenguinWife = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_MayorPenguinWife_Laugh, ANIM_MayorPenguinWife_Idle, 0, MSG_Outro_0057)
    Return
    End
};

EvtScript EVS_NpcInit_MayorPenguinWife = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_MayorPenguinWife))
    Return
    End
};

EvtScript EVS_NpcInteract_Penguin_01 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Penguin_Talk, ANIM_Penguin_Idle, 0, MSG_Outro_0062)
    Return
    End
};

EvtScript EVS_NpcInit_Penguin_01 = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Penguin_01))
    Return
    End
};

EvtScript EVS_NpcInteract_Penguin_02 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Penguin_Talk, ANIM_Penguin_Idle, 0, MSG_Outro_0063)
    Return
    End
};

EvtScript EVS_NpcInit_Penguin_02 = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Penguin_02))
    Return
    End
};

EvtScript EVS_NpcInteract_Moustafa = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Moustafa_Shout, ANIM_Moustafa_Idle, 0, MSG_Outro_0058)
    Return
    End
};

EvtScript EVS_NpcInit_Moustafa = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Moustafa))
    Return
    End
};

EvtScript EVS_NpcInteract_Mouser = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Purple_Talk, ANIM_Mouser_Purple_Idle, 0, MSG_Outro_005E)
    Return
    End
};

EvtScript EVS_NpcInit_Mouser = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Mouser))
    Return
    End
};

EvtScript EVS_NpcInteract_Boo_01 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Boo_Talk, ANIM_Boo_Idle, 0, MSG_Outro_005D)
    Return
    End
};

EvtScript EVS_NpcInit_Boo_01 = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Boo_01))
    Return
    End
};

EvtScript EVS_NpcInteract_Boo_02 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Boo_Tan_Talk, ANIM_Boo_Tan_Idle, 0, MSG_Outro_005F)
    Return
    End
};

EvtScript EVS_NpcInit_Boo_02 = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Boo_02))
    Return
    End
};

EvtScript EVS_NpcInteract_Toad = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toad_Blue_Talk, ANIM_Toad_Blue_Idle, 0, MSG_Outro_0059)
    Return
    End
};

EvtScript EVS_NpcInit_Toad = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Toad))
    Return
    End
};

EvtScript EVS_NpcInteract_ToadGuard_01 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_ToadGuard_Red_Talk, ANIM_ToadGuard_Red_Idle, 0, MSG_Outro_005A)
    Return
    End
};

EvtScript EVS_NpcInit_ToadGuard_01 = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_ToadGuard_01))
    Return
    End
};

EvtScript EVS_Guard_StopPlayer = {
    Call(DisablePlayerInput, true)
    Call(NpcFacePlayer, NPC_ToadGuard_02, 0)
    Wait(5)
    Call(SpeakToPlayer, NPC_ToadGuard_02, ANIM_ToadGuard_Yellow_Talk, ANIM_ToadGuard_Yellow_Idle, 0, MSG_Outro_005C)
    Wait(10)
    Call(SetPlayerSpeed, Float(4.0))
    Call(PlayerMoveTo, 610, 110, 0)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_NpcInteract_ToadGuard_02 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_ToadGuard_Yellow_Talk, ANIM_ToadGuard_Yellow_Idle, 0, MSG_Outro_005B)
    Return
    End
};

EvtScript EVS_NpcInit_ToadGuard_02 = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_ToadGuard_02))
    BindTrigger(Ref(EVS_Guard_StopPlayer), TRIGGER_FLOOR_TOUCH, COLLIDER_deilie, 1, 0)
    Return
    End
};

AnimID LimitAnims_YoshiLeader[] = {
    ANIM_VillageLeader_Still,
    ANIM_VillageLeader_Idle,
    ANIM_VillageLeader_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Yoshi[] = {
    ANIM_Yoshi_Green_Still,
    ANIM_Yoshi_Green_Idle,
    ANIM_Yoshi_Green_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_YoshiKid[] = {
    ANIM_YoshiKid_Green_Still,
    ANIM_YoshiKid_Green_Idle,
    ANIM_YoshiKid_Green_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Yoshis[] = {
    {
        .id = NPC_YoshiLeader,
        .pos = { 70.0f, 0.0f, -30.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_LeaderYoshi,
        .settings = &NpcSettings_Yoshi,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = YOSHI_LEADER_ANIMS,
        .limitAnimations = LimitAnims_YoshiLeader,
        .tattle = MSG_NpcTattle_VillageLeader,
    },
    {
        .id = NPC_Yoshi,
        .pos = { 70.0f, 0.0f, 400.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_Yoshi,
        .settings = &NpcSettings_Yoshi,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = YOSHI_GREEN_ANIMS,
        .limitAnimations = LimitAnims_Yoshi,
        .tattle = MSG_NpcTattle_GenericYoshi,
    },
    {
        .id = NPC_YoshiKid,
        .pos = { 160.0f, 0.0f, 540.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_YoshiKid,
        .settings = &NpcSettings_YoshiKid,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = YOSHI_KID_GREEN_ANIMS,
        .limitAnimations = LimitAnims_YoshiKid,
        .tattle = MSG_NpcTattle_GreenYoshiKid,
    },
};

AnimID LimitAnims_MayorPenguin[] = {
    ANIM_MayorPenguin_Still,
    ANIM_MayorPenguin_Idle,
    ANIM_MayorPenguin_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_MayorPenguinWife[] = {
    ANIM_MayorPenguinWife_Still,
    ANIM_MayorPenguinWife_Idle,
    ANIM_MayorPenguinWife_Laugh,
    ANIM_LIST_END
};

AnimID LimitAnims_Penguin[] = {
    ANIM_Penguin_Still,
    ANIM_Penguin_Idle,
    ANIM_Penguin_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Penguins[] = {
    {
        .id = NPC_MayorPenguin,
        .pos = { 150.0f, 0.0f, 105.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_MayorPenguin,
        .settings = &NpcSettings_Penguin,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MAYOR_PENGUIN_ANIMS,
        .limitAnimations = LimitAnims_MayorPenguin,
        .tattle = MSG_NpcTattle_MayorPenguin,
    },
    {
        .id = NPC_MayorPenguinWife,
        .pos = { 200.0f, 0.0f, 105.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_MayorPenguinWife,
        .settings = &NpcSettings_Penguin,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MAYOR_PENGUIN_WIFE_ANIMS,
        .limitAnimations = LimitAnims_MayorPenguinWife,
        .tattle = MSG_NpcTattle_MayorPenguinWife,
    },
    {
        .id = NPC_Penguin_01,
        .pos = { 115.0f, 0.0f, 540.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Penguin_01,
        .settings = &NpcSettings_Penguin,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
        .limitAnimations = LimitAnims_Penguin,
    },
    {
        .id = NPC_Penguin_02,
        .pos = { 208.0f, 0.0f, 540.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_Penguin_02,
        .settings = &NpcSettings_Penguin,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
        .limitAnimations = LimitAnims_Penguin,
    },
};

AnimID LimitAnims_Moustafa[] = {
    ANIM_Moustafa_Still,
    ANIM_Moustafa_Idle,
    ANIM_Moustafa_Shout,
    ANIM_LIST_END
};

AnimID LimitAnims_Mouser[] = {
    ANIM_Mouser_Blue_Still,
    ANIM_Mouser_Blue_Idle,
    ANIM_Mouser_Blue_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Mousers[] = {
    {
        .id = NPC_Moustafa,
        .pos = { -60.0f, 0.0f, -20.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Moustafa,
        .settings = &NpcSettings_Mouser,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSTAFA_ANIMS,
        .limitAnimations = LimitAnims_Moustafa,
        .tattle = MSG_NpcTattle_Moustafa,
    },
    {
        .id = NPC_Mouser,
        .pos = { -100.0f, 0.0f, -50.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Mouser,
        .settings = &NpcSettings_Mouser,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_PURPLE_ANIMS,
        .limitAnimations = LimitAnims_Mouser,
    },
};

AnimID LimitAnims_Boos[] = {
    ANIM_Boo_Still,
    ANIM_Boo_Idle,
    ANIM_Boo_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Boos[] = {
    {
        .id = NPC_Boo_01,
        .pos = { 270.0f, 20.0f, 175.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_Boo_01,
        .settings = &NpcSettings_Boo,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
        .limitAnimations = LimitAnims_Boos,
    },
    {
        .id = NPC_Boo_02,
        .pos = { 320.0f, 20.0f, 200.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_Boo_02,
        .settings = &NpcSettings_Boo,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = GUSTY_BOO_ANIMS,
        .limitAnimations = LimitAnims_Boos,
    },
};

AnimID LimitAnims_Toad[] = {
    ANIM_Toad_Red_Still,
    ANIM_Toad_Red_Idle,
    ANIM_Toad_Red_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_ToadGuard[] = {
    ANIM_ToadGuard_Red_Still,
    ANIM_ToadGuard_Red_Idle,
    ANIM_ToadGuard_Red_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Toads[] = {
    {
        .id = NPC_Toad,
        .pos = { -25.0f, 0.0f, 200.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_Toad,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .limitAnimations = LimitAnims_Toad,
    },
    {
        .id = NPC_ToadGuard_01,
        .pos = { -50.0f, 0.0f, -200.0f },
        .yaw = 90,
        .init = &EVS_NpcInit_ToadGuard_01,
        .settings = &NpcSettings_ToadGuard,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
        .limitAnimations = LimitAnims_ToadGuard,
    },
    {
        .id = NPC_ToadGuard_02,
        .pos = { 560.0f, 20.0f, 100.0f },
        .yaw = 270,
        .init = &EVS_NpcInit_ToadGuard_02,
        .settings = &NpcSettings_ToadGuard,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_YELLOW_ANIMS,
        .limitAnimations = LimitAnims_ToadGuard,
    },
};

NpcGroupList EpilogueNPCs = {
    NPC_GROUP(NpcData_Yoshis),
    NPC_GROUP(NpcData_Penguins),
    NPC_GROUP(NpcData_Mousers),
    NPC_GROUP(NpcData_Boos),
    NPC_GROUP(NpcData_Toads),
    {}
};
