#include "kkj_10.h"

EvtScript N(EVS_CapturePeach_Early) = {
    Call(DisablePlayerInput, true)
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_EMOTE_IDEA, SOUND_SPACE_DEFAULT)
    Call(ShowEmote, NPC_SELF, EMOTE_EXCLAMATION, 0, 20, EMOTER_NPC, 0, 0, 0, 0)
    Call(NpcFacePlayer, NPC_SELF, 5)
    Wait(20)
    Call(PlayerFaceNpc, NPC_SELF, false)
    Call(SetPlayerAnimation, ANIM_Peach2_Gasp)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_IdleFlashlight)
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_TalkFlashlight, ANIM_WorldKoopatrol_IdleFlashlight, 0, MSG_Peach_0174)
    Call(N(GetApproachPeachPos), NPC_SELF, 100, LVar3, LVar0, LVar2)
    IfNe(LVar3, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_RunFlashlight)
        Call(SetNpcSpeed, NPC_SELF, Float(5.0))
        Call(NpcMoveTo, NPC_SELF, LVar0, LVar2, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_IdleFlashlight)
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_TalkFlashlight, ANIM_WorldKoopatrol_IdleFlashlight, 0, MSG_Peach_0175)
    Call(SetPlayerAnimation, ANIM_Peach2_ForwardSad)
    Wait(20)
    Call(GotoMapSpecial, Ref("kkj_14"), kkj_14_ENTRY_B, TRANSITION_PEACH_CAPTURED)
    Wait(100)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_01_Early) = {
    Thread
        Set(LVar1, 0)
        Loop(0)
            Call(N(UpdateSearchlight), LVar0, 100, 90, 0, 40, 130, 0)
            IfNe(LVar0, 0)
                IfEq(LVar1, 0)
                    Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Early)))
                    Set(LVar1, 1)
                EndIf
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcSpeed, NPC_SELF, Float(2.0))
    Loop(0)
        Call(NpcMoveTo, NPC_SELF, -240, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, -240, 240, 0, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, 0, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, 0, 240, -240, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, -240, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, -240, 240, -240, 0)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, -240, 0, 0)
        Call(GetAngleBetweenPoints, LVar0, -240, 0, -240, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_02_Early) = {
    Thread
        Set(LVar1, 0)
        Loop(0)
            Call(N(UpdateSearchlight), LVar0, 100, 90, 0, 40, 131, 1)
            IfNe(LVar0, 0)
                IfEq(LVar1, 0)
                    Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Early)))
                    Set(LVar1, 1)
                EndIf
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcSpeed, NPC_SELF, Float(2.0))
    Loop(0)
        Call(NpcMoveTo, NPC_SELF, 240, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, 240, 240, 240, 0)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, 240, 0, 0)
        Call(GetAngleBetweenPoints, LVar0, 240, 0, 240, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, 240, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, 240, 240, 0, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, 0, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, 0, 240, 240, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_01_Early) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_WalkFlashlight)
    Call(SetNpcPos, NPC_SELF, -240, 0, 0)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_01_Early)))
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_02_Early) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_WalkFlashlight)
    Call(SetNpcPos, NPC_SELF, 0, 0, 240)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_02_Early)))
    Return
    End
};

AnimID N(LimitAnims_Koopatrol_Early)[] = {
    ANIM_WorldKoopatrol_IdleFlashlight,
    ANIM_WorldKoopatrol_WalkFlashlight,
    ANIM_WorldKoopatrol_RunFlashlight,
    ANIM_WorldKoopatrol_TalkFlashlight,
    ANIM_LIST_END
};

NpcData N(NpcData_Koopatrol_Early)[] = {
    {
        .id = NPC_Koopatrol_01,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_01_Early),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
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
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Early),
    },
};

NpcGroupList N(EarlyNPCs) = {
    NPC_GROUP(N(NpcData_Koopatrol_Early)),
    {}
};
