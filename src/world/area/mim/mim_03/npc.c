#include "mim_03.h"

#include "world/common/npc/Oaklie/idle.inc.c"

EvtScript EVS_NpcInteract_Oaklie = {
    Call(DisablePlayerInput, true)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_BOW_JOINED_PARTY)
            IfEq(AF_MIM03_ToggleDialogue_Oaklie, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Oaklie_Talk, ANIM_Oaklie_Idle, 0, MSG_CH3_0009)
                Set(AF_MIM03_ToggleDialogue_Oaklie, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Oaklie_Talk, ANIM_Oaklie_Idle, 0, MSG_CH3_000A)
                Set(AF_MIM03_ToggleDialogue_Oaklie, false)
            EndIf
        CaseLt(STORY_CH5_REACHED_LAVA_LAVA_ISLAND)
            IfEq(AF_MIM03_ToggleDialogue_Oaklie, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Oaklie_Talk, ANIM_Oaklie_Idle, 0, MSG_CH3_000B)
                Set(AF_MIM03_ToggleDialogue_Oaklie, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Oaklie_Talk, ANIM_Oaklie_Idle, 0, MSG_CH3_000C)
                Set(AF_MIM03_ToggleDialogue_Oaklie, false)
            EndIf
        CaseGe(STORY_CH5_REACHED_LAVA_LAVA_ISLAND)
            IfEq(AF_MIM03_ToggleDialogue_Oaklie, false)
                Call(SpeakToPlayer, NPC_SELF, ANIM_Oaklie_Talk, ANIM_Oaklie_Idle, 0, MSG_CH3_000D)
                Set(AF_MIM03_ToggleDialogue_Oaklie, true)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Oaklie_Talk, ANIM_Oaklie_Idle, 0, MSG_CH3_000E)
                Set(AF_MIM03_ToggleDialogue_Oaklie, false)
            EndIf
    EndSwitch
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_NpcInit_Oaklie = {
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Oaklie))
    Return
    End
};

NpcData NpcData_Oaklie = {
    .id = NPC_Oaklie,
    .pos = { 0.0f, 32.0f, 0.0f },
    .yaw = 270,
    .init = &EVS_NpcInit_Oaklie,
    .settings = &NpcSettings_Oaklie,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = OAKLIE_ANIMS,
    .tattle = MSG_NpcTattle_Oaklie,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Oaklie),
    {}
};
