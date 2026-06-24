#include "kkj_10.h"

AnimID N(LimitAnims_Koopatrol_Later)[] = {
    ANIM_WorldKoopatrol_Anim00,
    ANIM_WorldKoopatrol_Anim01,
    ANIM_WorldKoopatrol_Anim02,
    ANIM_WorldKoopatrol_Anim04,
    ANIM_WorldKoopatrol_Anim05,
    ANIM_WorldKoopatrol_Anim06,
    ANIM_WorldKoopatrol_Anim07,
    ANIM_WorldKoopatrol_Anim08,
    ANIM_WorldKoopatrol_Anim09,
    ANIM_WorldKoopatrol_Anim12,
    ANIM_WorldKoopatrol_Anim14,
    ANIM_WorldKoopatrol_Anim1B,
    ANIM_LIST_END
};

EvtScript N(EVS_CapturePeach_Later) = {
    Call(DisablePlayerInput, true)
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(PreventNextPeachDisguise)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_EMOTE_IDEA, SOUND_SPACE_DEFAULT)
    Call(ShowEmote, NPC_SELF, EMOTE_EXCLAMATION, 0, 20, EMOTER_NPC, 0, 0, 0, 0)
    Call(NpcFacePlayer, NPC_SELF, 5)
    Wait(20)
    Call(PlayerFaceNpc, NPC_SELF, false)
    Call(SetPlayerAnimation, ANIM_Peach2_Gasp)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Anim02)
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 0, MSG_Peach_0174)
    Call(N(GetApproachPeachPos), NPC_SELF, 100, LVar3, LVar0, LVar2)
    IfNe(LVar3, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Anim07)
        Call(SetNpcSpeed, NPC_SELF, Float(5.0))
        Call(NpcMoveTo, NPC_SELF, LVar0, LVar2, 0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Anim02)
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 0, MSG_Peach_0175)
    Call(SetPlayerAnimation, ANIM_Peach2_ForwardSad)
    Wait(20)
    Call(GotoMapSpecial, Ref("kkj_14"), kkj_14_ENTRY_B, TRANSITION_PEACH_CAPTURED)
    Wait(100)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_01_Later) = {
    Thread
        Set(LVar2, 0)
        Loop(0)
            Call(N(UpdateSearchlight), LVar0, 100, 90, 0, 40, 130, 0)
            IfEq(LVar2, 0)
                Call(GetPeachDisguise, LVar1)
                IfEq(LVar1, PEACH_DISGUISE_NONE)
                    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_CANT_INTERACT, true)
                    IfNe(LVar0, 0)
                        Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Later)))
                        Set(LVar2, 1)
                    EndIf
                Else
                    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_CANT_INTERACT, false)
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
        Call(GetAngleBetweenPoints, LVar0, -240, 240, -240, -50)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, -240, -50, 0)
        Call(GetAngleBetweenPoints, LVar0, -240, -50, -240, 240)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcIdle_Koopatrol_02_Later) = {
    Thread
        Set(LVar2, 0)
        Loop(0)
            Call(N(UpdateSearchlight), LVar0, 100, 90, 0, 40, 131, 1)
            IfEq(LVar2, 0)
                Call(GetPeachDisguise, LVar1)
                IfEq(LVar1, PEACH_DISGUISE_NONE)
                    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_CANT_INTERACT, false)
                    IfNe(LVar0, 0)
                        Call(BindNpcAI, NPC_SELF, Ref(N(EVS_CapturePeach_Later)))
                        Set(LVar2, 1)
                    EndIf
                Else
                    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_CANT_INTERACT, false)
                EndIf
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcSpeed, NPC_SELF, Float(2.0))
    Loop(0)
        Call(NpcMoveTo, NPC_SELF, 240, 240, 0)
        Call(GetAngleBetweenPoints, LVar0, 240, 240, 240, -50)
        Call(InterpNpcYaw, NPC_SELF, LVar0, 15)
        Call(NpcMoveTo, NPC_SELF, 240, -50, 0)
        Call(GetAngleBetweenPoints, LVar0, 240, -50, 240, 240)
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

EvtScript N(EVS_NpcInteract_Koopatrol_01_Later) = {
    Call(DisablePlayerInput, true)
    Call(GetSelfVar, 0, LVar0)
    IfEq(LVar0, 0)
        Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 5, MSG_Peach_013C)
        Call(SetSelfVar, 0, 1)
    Else
        Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 5, MSG_Peach_013D)
        Call(SetSelfVar, 0, 0)
    EndIf
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript N(EVS_NpcInteract_Koopatrol_02_Later) = {
    Call(DisablePlayerInput, true)
    Call(GetPeachDisguise, LVar0)
    IfEq(LVar0, PEACH_DISGUISE_CLUBBA)
        Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 5, MSG_Peach_0140)
    Else
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 0)
            Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 5, MSG_Peach_013E)
            Call(SetSelfVar, 0, 1)
        Else
            Call(SpeakToPlayer, NPC_SELF, ANIM_WorldKoopatrol_Anim09, ANIM_WorldKoopatrol_Anim02, 5, MSG_Peach_013F)
            Call(SetSelfVar, 0, 0)
        EndIf
    EndIf
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_01_Later) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Anim05)
    Call(SetNpcPos, NPC_SELF, -240, 0, -50)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_01_Later)))
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Koopatrol_01_Later)))
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopatrol_02_Later) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldKoopatrol_Anim05)
    Call(SetNpcPos, NPC_SELF, 0, 0, 240)
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Koopatrol_02_Later)))
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Koopatrol_02_Later)))
    Return
    End
};

NpcData N(NpcData_Koopatrol_Later)[] = {
    {
        .id = NPC_Koopatrol_01,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_01_Later),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Later),
    },
    {
        .id = NPC_Koopatrol_02,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Koopatrol_02_Later),
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Later),
    },
};

NpcGroupList N(LaterNPCs) = {
    NPC_GROUP(N(NpcData_Koopatrol_Later)),
    {}
};
