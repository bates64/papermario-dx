
#include "sbk_30.h"

#include "world/common/npc/Kolorado/idle.inc.c"
#include "world/common/npc/Archeologist/idle.inc.c"

LetterDelivery N(LetterDelivery_Kolorado) = {
    .recipientID = NPC_Kolorado,
    .recipientTalk = ANIM_Kolorado_Talk,
    .recipientIdle = ANIM_Kolorado_Idle,
    .msgGreeting = MSG_CH2_004A,
    .msgCancelled = MSG_CH2_004B,
    .msgDelivered = MSG_CH2_004C,
    .msgRecieved = MSG_CH2_004D,
    .letters = { ITEM_LETTER_TO_KOLORADO },
    .reward = ITEM_STAR_PIECE,
};

EvtScript N(EVS_ArtifactPrompt) = {
    Set(GF_SBK_GaveArtifactToKolorado, true)
    Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0044)
    EVT_GIVE_REWARD(ITEM_STAR_PIECE)
    Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0045)
    Return
    End
};

EvtScript N(EVS_NpcInteract_Kolorado) = {
    Call(GetNpcAnimation, NPC_SELF, LVar9)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Kolorado_Idle)
    IfEq(GF_SBK30_Met_Kolorado, false)
        Call(AdjustCam, CAM_DEFAULT, Float(4.0), 0, Float(300.0), Float(15.0), Float(-7.5))
        Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0037)
        Call(ResetCam, CAM_DEFAULT, 4)
        Set(GF_SBK30_Met_Kolorado, true)
        Goto(50)
    EndIf
    IfEq(GF_SBK_GaveArtifactToKolorado, true)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0046)
        Goto(50)
    EndIf
    Call(HasItem, ITEM_ARTIFACT, LVar0)
    IfEq(LVar0, 1)
        IfEq(GF_SBK_KeptArtifactFromKolorado, true)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0043)
        Else
            Set(GF_SBK_KeptArtifactFromKolorado, true)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0040)
        EndIf
        EVT_CHOOSE_KEY_ITEM_ONLY(ITEM_ARTIFACT, NPC_Kolorado)
        Switch(LVar0)
            CaseGe(1)
                ExecWait(N(EVS_ArtifactPrompt))
                Goto(50)
            CaseDefault
                Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0041)
                EVT_CHOOSE_KEY_ITEM_ONLY(ITEM_ARTIFACT, NPC_Kolorado)
                Switch(LVar0)
                    CaseGe(1)
                        ExecWait(N(EVS_ArtifactPrompt))
                    CaseDefault
                        Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0042)
                        Goto(50)
                EndSwitch
        EndSwitch
    EndIf
    IfGe(GB_StoryProgress, STORY_CH2_ARRIVED_AT_DRY_DRY_OUTPOST)
        IfEq(GF_DRO02_Sheek_SpokeTo, false)
            IfEq(AF_SBK30_KoloradoHint1, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0039)
                Set(AF_SBK30_KoloradoHint1, true)
                Goto(50)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_003A)
                Goto(50)
            EndIf
        EndIf
        IfEq(GF_DRO02_Sheek_AskedAboutRuins, false)
            IfEq(AF_SBK30_KoloradoHint2, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_003B)
                Set(GF_SBK30_Kolorado_SharedRumorAboutMoustafa, true)
                Set(AF_SBK30_KoloradoHint2, true)
                Goto(50)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_003C)
                Goto(50)
            EndIf
        EndIf
        IfEq(GF_SBK30_Kolorado_SharedRumorAboutMoustafa, true)
            IfEq(GF_DRO02_Sheek_AskedAboutMoustafa, false)
                IfEq(AF_SBK30_KoloradoHint3, false)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_003D)
                    Set(AF_SBK30_KoloradoHint3, true)
                    Goto(50)
                Else
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_003E)
                    Goto(50)
                EndIf
            EndIf
        EndIf
        Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_003F)
        Goto(50)
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_CH2_0038)
    Label(50)
    Label(90)
    Call(GetCurrentPartnerID, LVar0)
    IfEq(LVar0, PARTNER_KOOPER)
        IfEq(GF_SBK30_KooperMetKolorado, false)
            Set(GF_SBK30_KooperMetKolorado, true)
            Call(DisablePartnerAI, false)
            Call(SpeakToNpc, NPC_PARTNER, ANIM_WorldKooper_CelebrateLoop, ANIM_WorldKooper_Idle, 0, NPC_SELF, MSG_CH2_0047)
            Call(SpeakToNpc, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, NPC_PARTNER, MSG_CH2_0048)
            Call(SpeakToNpc, NPC_PARTNER, ANIM_WorldKooper_CelebrateLoop, ANIM_WorldKooper_Idle, 0, NPC_SELF, MSG_CH2_0049)
            Call(EnablePartnerAI)
        EndIf
    EndIf
    Call(SetNpcAnimation, NPC_SELF, LVar9)
    Set(LVar0, Ref(N(LetterDelivery_Kolorado)))
    ExecWait(EVS_TryLetterDelivery)
    Return
    End
};

EvtScript N(EVS_NpcIdle_Kolorado) = {
    Loop(0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Kolorado_Idle)
        Wait(15)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Kolorado_Walk)
        Call(NpcMoveTo, NPC_SELF, 97, -179, 120)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Kolorado_Idle)
        Wait(15)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Kolorado_Walk)
        Call(NpcMoveTo, NPC_SELF, 200, -100, 120)
    EndLoop
    Return
    End
};

EvtScript N(EVS_NpcIdle_KoloradoPanic) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_Kolorado_Panic)
    Call(SetNpcSpeed, NPC_SELF, Float(4.0))
    Call(NpcMoveTo, NPC_SELF, 145, -145, 0)
    Label(0)
    Call(RandInt, 30, LVar0)
    Add(LVar0, 1)
    Wait(LVar0)
    Call(GetNpcYaw, NPC_SELF, LVar0)
    Add(LVar0, 180)
    Call(InterpNpcYaw, NPC_SELF, LVar0, 5)
    Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kolorado) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq(sbk_30_ENTRY_4)
        CaseOrEq(sbk_30_ENTRY_5)
            Call(SetNpcPos, NPC_SELF, 210, 0, -210)
            Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KoloradoPanic)))
        EndCaseGroup
        CaseDefault
            Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Kolorado)))
            Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Kolorado)))
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcIdle_Archeologist_01) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_Archeologist_Talk)
    Label(0)
    Call(RandInt, 50, LVar0)
    Add(LVar0, 1)
    Wait(LVar0)
    Call(GetNpcYaw, NPC_SELF, LVar0)
    Add(LVar0, 180)
    Call(InterpNpcYaw, NPC_SELF, LVar0, 5)
    Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcInteract_Archeologist_01) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_GOT_PULSE_STONE)
            IfEq(AF_SBK30_ToggleDialogue_Archeologist1, false)
                Set(LVar0, MSG_CH2_004E)
                Set(AF_SBK30_ToggleDialogue_Archeologist1, true)
            Else
                Set(LVar0, MSG_CH2_004F)
                Set(AF_SBK30_ToggleDialogue_Archeologist1, false)
            EndIf
        CaseDefault
            IfEq(GF_SBK_GaveArtifactToKolorado, false)
                Set(LVar0, MSG_CH2_0050)
            Else
                Set(LVar0, MSG_CH2_0051)
            EndIf
    EndSwitch
    Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, LVar0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Archeologist_01) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Archeologist_01)))
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq(sbk_30_ENTRY_4)
        CaseOrEq(sbk_30_ENTRY_5)
            Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Archeologist_01)))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInteract_Archeologist_02) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_GOT_PULSE_STONE)
            IfEq(AF_SBK30_ToggleDialogue_Archeologist2, false)
                Set(LVar0, MSG_CH2_0052)
                Set(AF_SBK30_ToggleDialogue_Archeologist2, true)
            Else
                Set(LVar0, MSG_CH2_0053)
                Set(AF_SBK30_ToggleDialogue_Archeologist2, false)
            EndIf
        CaseDefault
            IfEq(GF_SBK_GaveArtifactToKolorado, false)
                Set(LVar0, MSG_CH2_0054)
            Else
                Set(LVar0, MSG_CH2_0055)
            EndIf
    EndSwitch
    Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, LVar0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Archeologist_02) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Archeologist_02)))
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq(sbk_30_ENTRY_4)
        CaseOrEq(sbk_30_ENTRY_5)
            Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Archeologist_01)))
        EndCaseGroup
    EndSwitch
    Return
    End
};

NpcData N(NpcData_Archeologist_02)[] = {
    {
        .id = NPC_Kolorado,
        .pos = { 200.0f, 0.0f, -100.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Kolorado),
        .settings = &N(NpcSettings_Kolorado),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = KOLORADO_ANIMS,
        .tattle = MSG_NpcTattle_SBK_Kolorado,
    },
    {
        .id = NPC_Archeologist_01,
        .pos = { 238.0f, 0.0f, -112.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 100 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_Archeologist_01),
        .settings = &N(NpcSettings_Archeologist),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = ARCHEOLOGIST_ANIMS,
        .tattle = MSG_NpcTattle_SBK_ExcavatorA,
    },
    {
        .id = NPC_Archeologist_02,
        .pos = { 170.0f, 0.0f, -190.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { 0, 0, 0 },
                .wanderSize = { 100 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_Archeologist_02),
        .settings = &N(NpcSettings_Archeologist),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = ARCHEOLOGIST_ANIMS,
        .tattle = MSG_NpcTattle_SBK_ExcavatorB,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Archeologist_02)),
    {}
};
