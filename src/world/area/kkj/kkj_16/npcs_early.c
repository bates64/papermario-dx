#include "kkj_16.h"
#include "sprite/player.h"


EvtScript N(EVS_CapturePeach_Early) = {
    Call(DisablePlayerInput, true)
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_EMOTE_IDEA, SOUND_SPACE_DEFAULT)
    Call(ShowEmote, NPC_SELF, EMOTE_EXCLAMATION, 0, 20, EMOTER_NPC, 0, 0, 0, 0)
    Call(NpcFacePlayer, NPC_SELF, 0)
    Wait(20)
    Call(PlayerFaceNpc, NPC_SELF, false)
    Call(SetPlayerAnimation, ANIM_Peach2_Gasp)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Idle)
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Talk, ANIM_WorldKoopatrol_Idle, 0, MSG_Peach_0174)
    Call(N(GetApproachPeachPos), NPC_SELF, 50, LVar3, LVar0, LVar2)
    IfNe(LVar3, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Run)
        Call(SetNpcSpeed, NPC_SELF, Float(5.0))
        Call(NpcMoveTo, NPC_SELF, LVar0, LVar2, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Idle)
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Talk, ANIM_WorldKoopatrol_Idle, 0, MSG_Peach_0175)
    Call(SetPlayerAnimation, ANIM_Peach2_ForwardSad)
    Wait(20)
    Call(GotoMapSpecial, Ref("kkj_14"), kkj_14_ENTRY_B, TRANSITION_PEACH_CAPTURED)
    Wait(100)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_02_Early) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
    Thread
        Loop(0)
            Call(N(CheckPlayerInSight), LVar0, 85, 60, 38)
            IfEq(LVar0, 1)
                Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Early)))
                Return
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcSpeed, NPC_SELF, Float(1.7))
    Loop(0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Idle)
        Wait(20)
        Call(InterpNpcYaw, NPC_SELF, 90, 15)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
        Call(NpcMoveTo, NPC_SELF, 280, 50, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Idle)
        Wait(20)
        Call(InterpNpcYaw, NPC_SELF, 270, 15)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
        Call(NpcMoveTo, NPC_SELF, 80, 50, 0)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_03_Early) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
    Thread
        Loop(0)
            Call(N(CheckPlayerInSight), LVar0, 85, 60, 38)
            IfEq(LVar0, 1)
                Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Early)))
                Return
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcSpeed, NPC_SELF, Float(2.0))
    Loop(0)
        Call(NpcMoveTo, NPC_SELF, -248, -80, 0)
        Call(NpcMoveTo, NPC_SELF, -84, -80, 0)
        Call(NpcMoveTo, NPC_SELF, -84, -15, 0)
        Call(NpcMoveTo, NPC_SELF, -88, -15, 0)
        Call(NpcMoveTo, NPC_SELF, -88, 50, 0)
        Call(NpcMoveTo, NPC_SELF, -252, 50, 0)
        Call(NpcMoveTo, NPC_SELF, -252, -15, 0)
        Call(NpcMoveTo, NPC_SELF, -248, -15, 0)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_04_Early) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
    Thread
        Loop(0)
            Call(N(CheckPlayerInSight), LVar0, 85, 60, 38)
            IfEq(LVar0, 1)
                Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Early)))
                Return
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcSpeed, NPC_SELF, Float(1.7))
    Loop(0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Idle)
        Wait(30)
        Call(InterpNpcYaw, NPC_SELF, 270, 15)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
        Call(NpcMoveTo, NPC_SELF, -600, 50, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Idle)
        Wait(30)
        Call(InterpNpcYaw, NPC_SELF, 90, 15)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Walk)
        Call(NpcMoveTo, NPC_SELF, -420, 50, 0)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcInit_HammerBros_Early) = {
    IfNe(GB_StoryProgress, STORY_CH2_BEGAN_PEACH_MISSION)
        Call(RemoveNpc, NPC_SELF)
        Return
    EndIf
    Call(SetNpcPos, NPC_SELF, -700, 0, 50)
    Call(InterpNpcYaw, NPC_SELF, 270, 1)
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_01_Early) = {
    IfNe(GB_StoryProgress, STORY_CH2_BEGAN_PEACH_MISSION)
        Call(RemoveNpc, NPC_SELF)
        Return
    EndIf
    Call(SetNpcPos, NPC_SELF, -740, 0, 50)
    Call(InterpNpcYaw, NPC_SELF, 90, 1)
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_02_Early) = {
    Call(SetNpcPos, NPC_SELF, 180, 0, 50)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_02_Early)))
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_03_Early) = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_FLYING, false)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, true)
    Call(SetNpcPos, NPC_SELF, -250, 0, -15)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_03_Early)))
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_04_Early) = {
    Call(SetNpcPos, NPC_SELF, -510, 0, 50)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_04_Early)))
    Return
    End
};

AnimID N(LimitAnims_HammerBros_Early)[] = {
    ANIM_HammerBros_Still,
    ANIM_HammerBros_Idle,
    ANIM_HammerBros_Walk,
    ANIM_HammerBros_CarryFast,
    ANIM_HammerBros_Talk,
    ANIM_HammerBros_Lift,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Koopatrol_Early)[] = {
    ANIM_WorldKoopatrol_Still,
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_Walk,
    ANIM_WorldKoopatrol_Run,
    ANIM_WorldKoopatrol_Talk,
    ANIM_WorldKoopatrol_Lift,
    ANIM_WorldKoopatrol_CarryFast,
    ANIM_LIST_END
};

NpcData N(NpcData_Minions_Early)[] = {
    {
        .id = NPC_HammerBros,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_HammerBros_Early),
        .settings = &N(NpcSettings_HammerBros),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = HAMMER_BROS_ANIMS,
        .limitAnimations = N(LimitAnims_HammerBros_Early),
    },
    {
        .id = NPC_Koopatrol_01,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_01_Early),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Early),
    },
    {
        .id = NPC_Koopatrol_02,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_02_Early),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Early),
    },
    {
        .id = NPC_Koopatrol_03,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_03_Early),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Early),
    },
    {
        .id = NPC_Koopatrol_04,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_04_Early),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Early),
    },
};

NpcGroupList N(EarlyNPCs) = {
    NPC_GROUP(N(NpcData_Minions_Early)),
    {}
};
