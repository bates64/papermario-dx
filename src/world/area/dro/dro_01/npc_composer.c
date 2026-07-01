#include "dro_01.h"
#include "sprite/player.h"
#include "world/common/npc/MusicianComposer/base.h"

EvtScript N(EVS_NpcInteract_Composer) = {
    IfEq(GF_DRO01_Gift_Melody, true)
        Call(FindItem, ITEM_MELODY, LVar0)
        IfNe(LVar0, -1)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0084)
            Return
        Else
            IfEq(GF_DRO01_Gift_ToldComposerAboutMelody, false)
                IfLt(GB_StoryProgress, STORY_CH7_BEGAN_PEACH_MISSION)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0085)
                    Call(SetPlayerAnimation, ANIM_Mario1_NodYes)
                    Wait(30)
                    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0086)
                    Set(GF_DRO01_Gift_ToldComposerAboutMelody, true)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfEq(AF_DRO01_ToggleDialogue_Composer, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_007C)
                Set(AF_DRO01_ToggleDialogue_Composer, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_007D)
                Set(AF_DRO01_ToggleDialogue_Composer, false)
            EndIf
        CaseLt(STORY_CH5_STAR_SPRIT_DEPARTED)
            IfEq(AF_DRO01_ToggleDialogue_Composer, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_007E)
                Set(AF_DRO01_ToggleDialogue_Composer, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_007F)
                Set(AF_DRO01_ToggleDialogue_Composer, false)
            EndIf
        CaseDefault
            IfEq(AF_DRO01_ToggleDialogue_Composer, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0080)
                Set(AF_DRO01_ToggleDialogue_Composer, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0081)
                Set(AF_DRO01_ToggleDialogue_Composer, false)
            EndIf
    EndSwitch
    EVT_CHOOSE_KEY_ITEM_ONLY(ITEM_LYRICS, NPC_ArtistToad)
    Switch(LVar0)
        CaseEq(ITEM_CHOICE_NONE)
        CaseEq(ITEM_CHOICE_CANCELED)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0082)
            Call(SetNpcAnimation, NPC_SELF, ANIM_Musician_Composer_Write)
            Wait(60)
            Call(SetNpcAnimation, NPC_SELF, ANIM_Musician_Composer_Idle)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 0, MSG_CH2_0083)
            EVT_GIVE_REWARD(ITEM_MELODY)
            Set(GF_DRO01_Gift_Melody, true)
            Return
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Composer) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Composer)))
    Return
    End
};
