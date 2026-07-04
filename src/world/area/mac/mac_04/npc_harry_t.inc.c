#include "mac_04.h"

EvtScript N(EVS_NpcInteract_HarryT) = {
    Set(LVar9, 0)
    IfGe(GB_StoryProgress, STORY_CH3_STAR_SPRIT_DEPARTED)
        IfLt(GB_StoryProgress, STORY_CH4_RETURNED_STOREROOM_KEY)
            Set(LVar9, 1)
        EndIf
    EndIf
    IfEq(LVar9, 1)
        Call(SpeakToPlayer, NPC_HarryT, ANIM_HarryT_Talk, ANIM_HarryT_Idle, 0, MSG_MAC_Housing_0001)
        EVT_CHOOSE_KEY_ITEM_ONLY(ITEM_STOREROOM_KEY, NPC_HarryT)
        Switch(LVar0)
            CaseEq(ITEM_CHOICE_CANCELED)
                Call(SpeakToPlayer, NPC_HarryT, ANIM_HarryT_Talk, ANIM_HarryT_Idle, 0, MSG_MAC_Housing_0002)
            CaseEq(ITEM_CHOICE_NONE)
            CaseDefault
                Call(SpeakToPlayer, NPC_HarryT, ANIM_HarryT_Talk, ANIM_HarryT_Idle, 0, MSG_MAC_Housing_0003)
                Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_GRAVITY, true)
                Call(SetNpcAnimation, NPC_HarryT, ANIM_HarryT_Run)
                Call(NpcMoveTo, NPC_HarryT, 295, -460, 0)
                Call(NpcMoveTo, NPC_HarryT, 230, -480, 0)
                Call(NpcJump0, NPC_HarryT, 198, 30, -480, 0)
                Call(NpcJump0, NPC_HarryT, 162, 40, -480, 0)
                Call(SetNpcAnimation, NPC_HarryT, ANIM_HarryT_Idle)
                Wait(20)
                Exec(N(EVS_ForceStoreroomUnlock))
                Call(SetNpcAnimation, NPC_HarryT, ANIM_HarryT_Run)
                Call(NpcMoveTo, NPC_HarryT, 200, -524, 0)
                Call(SetNpcPos, NPC_HarryT, 200, 30, -524)
                Call(SetNpcAnimation, NPC_HarryT, ANIM_HarryT_Idle)
                Call(InterpNpcYaw, NPC_HarryT, 180, 0)
                Call(PlayerFaceNpc, NPC_HarryT, false)
                Call(SpeakToPlayer, NPC_HarryT, ANIM_HarryT_Talk, ANIM_HarryT_Idle, 0, MSG_MAC_Housing_0005)
                Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_GRAVITY, false)
                Set(GB_StoryProgress, STORY_CH4_RETURNED_STOREROOM_KEY)
        EndSwitch
    Else
        ExecWait(EVS_ShopOwnerDialog)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_HarryT) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_HarryT)))
    IfGe(GB_StoryProgress, STORY_CH3_STAR_SPRIT_DEPARTED)
        IfLt(GB_StoryProgress, STORY_CH4_RETURNED_STOREROOM_KEY)
            Call(SetNpcAnimation, NPC_HarryT, ANIM_HarryT_Idle)
        EndIf
    EndIf
    Return
    End
};
