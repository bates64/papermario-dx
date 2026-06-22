#include "dro_02.h"
#include "effects.h"
#include "script_api/battle.h"

extern EvtScript N(EVS_NpcInit_Moustafa);
extern EvtScript N(EVS_NpcInit_DisguisedMoustafa);

#include "world/common/npc/Quizmo/quiz.inc.c"

#include "world/common/npc/Archeologist/wander.inc.c"
#include "world/common/npc/Dryite/idle.inc.c"
#include "world/common/npc/Dryite/wander.inc.c"
#include "world/common/npc/Merlee/idle.inc.c"
#include "world/common/npc/Mouser/idle.inc.c"
#include "world/common/npc/Toad/idle.inc.c"

#include "world/common/prefab/ToadHouse.inc.c"
#include "world/common/prefab/ToadHouse.data.inc.c"

LetterDelivery N(LetterDelivery_MrE) = {
    .recipientID = NPC_Dryite_01,
    .recipientTalk = ANIM_Dryite_Blue_Talk,
    .recipientIdle = ANIM_Dryite_Blue_Idle,
    .msgGreeting = MSG_CH2_0095,
    .msgCancelled = MSG_CH2_0096,
    .msgDelivered = MSG_CH2_0097,
    .msgRecieved = MSG_CH2_0098,
    .letters = { ITEM_LETTER_CHAIN_MR_E },
    .reward = ITEM_LETTER_CHAIN_MISS_T,
};

EvtScript N(EVS_NpcInteract_Archeologist) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfEq(GF_SBK30_Kolorado_SharedRumorAboutMoustafa, true)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, MSG_CH2_00B2)
            Else
                Switch(AB_DRO02_DialogueState_Archeologist)
                    CaseEq(0)
                        Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, MSG_CH2_00AF)
                        Set(AB_DRO02_DialogueState_Archeologist, 1)
                    CaseEq(1)
                        Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, MSG_CH2_00B0)
                        Set(AB_DRO02_DialogueState_Archeologist, 2)
                    CaseEq(2)
                        Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, MSG_CH2_00B1)
                        Set(AB_DRO02_DialogueState_Archeologist, 1)
                EndSwitch
            EndIf
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Archeologist_Talk, ANIM_Archeologist_Idle, 0, MSG_CH2_00B3)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Archeologist) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Archeologist)))
    IfGe(GB_StoryProgress, STORY_UNUSED_FFFFFFCC)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInteract_MrE) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfEq(GF_DRO02_Sheek_AskedAboutDesert, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_0091)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_0092)
            EndIf
        CaseLt(STORY_CH5_STAR_SPRIT_DEPARTED)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_0093)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_0094)
    EndSwitch
    Set(LVar0, Ref(N(LetterDelivery_MrE)))
    ExecWait(EVS_TryLetterDelivery)
    Return
    End
};

EvtScript N(EVS_NpcInit_MrE) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_MrE)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_02) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfEq(AF_DRO02_ToggleDialogue_Dryite2, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_CH2_00A1)
                Set(AF_DRO02_ToggleDialogue_Dryite2, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_CH2_00A2)
                Set(AF_DRO02_ToggleDialogue_Dryite2, false)
            EndIf
        CaseLt(STORY_CH5_STAR_SPRIT_DEPARTED)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_CH2_00A3)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_CH2_00A4)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_02) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_02)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_03) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_CH2_00A0)
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_03) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_03)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Mouser_01) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfEq(AF_DRO02_ToggleDialogue_Mouser1, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00A5)
                Set(AF_DRO02_ToggleDialogue_Mouser1, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00A6)
                Set(AF_DRO02_ToggleDialogue_Mouser1, false)
            EndIf
        CaseLt(STORY_CH5_STAR_SPRIT_DEPARTED)
            IfEq(AF_DRO02_ToggleDialogue_Mouser1, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00A7)
                Set(AF_DRO02_ToggleDialogue_Mouser1, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00A8)
                Set(AF_DRO02_ToggleDialogue_Mouser1, false)
            EndIf
        CaseDefault
            IfEq(AF_DRO02_ToggleDialogue_Mouser1, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00A9)
                Set(AF_DRO02_ToggleDialogue_Mouser1, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00AA)
                Set(AF_DRO02_ToggleDialogue_Mouser1, false)
            EndIf
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Mouser_01) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Mouser_01)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Mouser_02) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfEq(AF_DRO02_ToggleDialogue_Mouser2, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00AB)
                Set(AF_DRO02_ToggleDialogue_Mouser2, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00AC)
                Set(AF_DRO02_ToggleDialogue_Mouser2, false)
            EndIf
        CaseLt(STORY_CH5_STAR_SPRIT_DEPARTED)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00AD)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_00AE)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Mouser_02) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Mouser_02)))
    Return
    End
};

EvtScript N(EVS_NpcIdle_Mouser_03) = {
    Call(InterpNpcYaw, NPC_DisguisedMoustafa, 270, 0)
    Label(10)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Mouser_Purple_Gossip)
        Call(SetNpcAnimation, NPC_DisguisedMoustafa, ANIM_DisguisedMoustafa_Idle)
        Loop(50)
            Call(IsPlayerWithin, 200, 50, 100, LVar0)
            IfEq(LVar0, 1)
                Goto(20)
            EndIf
            Wait(1)
        EndLoop
        Call(SetNpcAnimation, NPC_SELF, ANIM_Mouser_Purple_Idle)
        Call(SetNpcAnimation, NPC_DisguisedMoustafa, ANIM_DisguisedMoustafa_TalkAlt)
        Loop(50)
            Call(IsPlayerWithin, 200, 50, 100, LVar0)
            IfEq(LVar0, 1)
                Goto(20)
            EndIf
            Wait(1)
        EndLoop
        Goto(10)
    Label(20)
    Call(SetNpcAnimation, NPC_DisguisedMoustafa, ANIM_DisguisedMoustafa_Idle)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Mouser_Purple_Run)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcAnimation, NPC_SELF, ANIM_Mouser_Purple_Run)
    Call(NpcMoveTo, NPC_SELF, 150, 18, 20)
    Call(EnableNpcBlur, NPC_SELF, true)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_RUN_AWAY, SOUND_SPACE_DEFAULT)
    Call(NpcMoveTo, NPC_SELF, -83, 11, 20 * DT)
    Call(NpcMoveTo, NPC_SELF, -239, 5, 20 * DT)
    Call(NpcMoveTo, NPC_SELF, -371, 5, 20 * DT)
    Call(NpcMoveTo, NPC_SELF, -487, 5, 20 * DT)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Set(GB_StoryProgress, STORY_CH2_SPOKE_WITH_SHEEK)
    Return
    End
};

EvtScript N(EVS_NpcInit_Mouser_03) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_Mouser_03)))
    IfGe(GB_StoryProgress, STORY_CH2_SPOKE_WITH_SHEEK)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_ToadHouse_SetDialogue) = {
    Set(LVar0, MSG_CH2_00D1)
    Set(LVar8, MSG_CH2_00D2)
    Set(LVar1, MSG_CH2_00D3)
    Set(LVar2, MSG_CH2_00D4)
    Set(LVar3, MSG_CH2_00D5)
    Return
    End
};

EvtScript N(EVS_ToadHouse_GetInBed) = {
    Exec(N(EVS_PlayRestMusic))
    Call(SetPlayerSpeed, Float(3.0))
    Call(PlayerMoveTo, -179, -198, 0)
    Thread
        Wait(15)
        Call(N(ToadHouse_CamSetFOV), 0, 40)
        Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
        Call(SetCamPitch, CAM_DEFAULT, 95, -61)
        Call(SetCamDistance, CAM_DEFAULT, 108)
        Call(SetCamPosA, CAM_DEFAULT, 202, 62)
        Call(SetCamPosB, CAM_DEFAULT, -89, -141)
        Call(SetCamPosC, CAM_DEFAULT, 0, 0)
        Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
        Call(PanToTarget, CAM_DEFAULT, 0, true)
    EndThread
    Call(PlayerMoveTo, -187, -267, 0)
    Call(InterpPlayerYaw, 230, 1)
    Call(HidePlayerShadow, true)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Call(SetPlayerImgFXFlags, IMGFX_FLAG_HOLD_DONE)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Idle, IMGFX_SET_ANIM, IMGFX_ANIM_GET_IN_BED, 1, 1, 0)
    Thread
        Wait(60)
        Call(SetPlayerAnimation, ANIM_MarioW2_SleepStanding)
    EndThread
    Wait(20)
    Thread
        Wait(81)
        Call(N(ToadHouse_CamSetFOV), 0, 25)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Call(PanToTarget, CAM_DEFAULT, 0, false)
    EndThread
    Return
    End
};

EvtScript N(EVS_ToadHouse_ReturnFromRest) = {
    Call(HidePlayerShadow, false)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Idle, IMGFX_CLEAR, 0, 0, 0, 0)
    Call(SetPlayerPos, -187, 0, -240)
    Call(SetPlayerSpeed, Float(3.0))
    Call(PlayerMoveTo, -168, -195, 0)
    Exec(N(EVS_SetupMusic))
    Return
    End
};

EvtScript N(EVS_NpcInit_ToadHouseKeeper) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_ToadHouseKeeper)))
    Return
    End
};

EvtScript N(EVS_NpcInit_Merlee) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Merlee)))
    Return
    End
};

NpcData N(PassiveNPCs)[] = {
    {
        .id = NPC_Archeologist,
        .pos = { -320.0f, 0.0f, -14.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_RECT,
                .centerPos  = { -303, 0, 22 },
                .wanderSize = { 146, 38 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_Archeologist),
        .settings = &N(NpcSettings_Archeologist_Wander),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = ARCHEOLOGIST_ANIMS,
        .tattle = MSG_NpcTattle_Archeologist,
    },
    {
        .id = NPC_Dryite_01,
        .pos = { -20.0f, 0.0f, 40.0f },
        .yaw = 270,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -20, 0, 40 },
                .wanderSize = { 60 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_MrE),
        .settings = &N(NpcSettings_Dryite_Wander),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteE,
    },
    {
        .id = NPC_DisguisedMoustafa,
        .pos = { 245.0f, 0.0f, -35.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_DisguisedMoustafa),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DISGUISED_MOUSTAFA_ANIMS,
        .tattle = MSG_NpcTattle_Sheek,
    },
    {
        .id = NPC_Toad,
        .pos = { -143.0f, 0.0f, -170.0f },
        .yaw = 180,
        .init = &N(EVS_NpcInit_ToadHouseKeeper),
        .settings = &N(NpcSettings_Toad),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_DRO_ToadHouseToad,
    },
    {
        .id = NPC_Merlee,
        .pos = { -130.0f, 0.0f, -400.0f },
        .yaw = 180,
        .init = &N(EVS_NpcInit_Merlee),
        .settings = &N(NpcSettings_Merlee),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MERLEE_ANIMS,
        .tattle = MSG_NpcTattle_Merlee,
    },
    {
        .id = NPC_Moustafa,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Moustafa),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSTAFA_ANIMS,
        .tattle = MSG_NpcTattle_Moustafa,
    },
    {
        .id = NPC_Dryite_02,
        .pos = { 25.0f, 0.0f, -38.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Dryite_02),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteF,
    },
    {
        .id = NPC_Dryite_03,
        .pos = { -375.0f, 0.0f, -10.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Dryite_03),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_VisitedShootingStarSummit,
    },
    {
        .id = NPC_Mouser_01,
        .pos = { -50.0f, 0.0f, -470.0f },
        .yaw = 180,
        .init = &N(EVS_NpcInit_Mouser_01),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_CrushingOnMerlee,
    },
    {
        .id = NPC_Mouser_02,
        .pos = { -270.0f, 0.0f, 91.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Mouser_02),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_TellsTales,
    },
    {
        .id = NPC_Mouser_03,
        .pos = { 210.0f, 0.0f, -35.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Mouser_03),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_PURPLE_ANIMS,
    },
    {
        .id = NPC_ChuckQuizmo,
        .pos = { -335.0f, 0.0f, 90.0f },
        .yaw = 270,
        .initVarCount = 1,
        .initVar = { .bytes = { 0, QUIZ_AREA_DRO, QUIZ_COUNT_DRO, QUIZ_MAP_DRO_02 } },
        .settings = &N(NpcSettings_ChuckQuizmo),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = QUIZMO_ANIMS,
        .tattle = MSG_NpcTattle_ChuckQuizmo,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(PassiveNPCs)),
    {},
};
