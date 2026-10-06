#pragma once
#include "idle.h"

#include "sprite/player.h"

#define EVAR_INTERACTED 0

EvtScript EVS_NpcAI_HurtPlant = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetNpcAnimation, NPC_SELF, ANIM_HurtPlant_Hiding)
    Call(SetSelfVar, EVAR_INTERACTED, false)
    Label(0)
        Call(GetSelfVar, EVAR_INTERACTED, LVar0)
        IfEq(LVar0, false)
            Wait(1)
            Goto(0)
        EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(DisablePlayerInput, true)
    Call(NpcFacePlayer, NPC_SELF, 0)
    Call(SetNpcAnimation, NPC_SELF, ANIM_HurtPlant_Reveal)
    Wait(15)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_HURT_PLANT_SHRIEK, SOUND_SPACE_DEFAULT)
    Wait(10)
    Call(SetPlayerAnimation, ANIM_Mario1_Flail)
    Wait(5)
    Call(SetNpcAnimation, NPC_SELF, ANIM_HurtPlant_Idle)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Call(StartBattle)
    Return
    End
};

EvtScript EVS_NpcInteract_HurtPlant = {
    Call(SetSelfVar, EVAR_INTERACTED, true)
    Return
    End
};

EvtScript EVS_NpcDefeat_HurtPlant = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_HurtPlant))
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

NpcSettings NpcSettings_HurtPlant = {
    .height = 20,
    .radius = 28,
    .level = ACTOR_LEVEL_HURT_PLANT,
    .doAI = &EVS_NpcAI_HurtPlant,
    .onInteract = &EVS_NpcInteract_HurtPlant,
    .onDefeat = &EVS_NpcDefeat_HurtPlant,
};

AnimID LimitAnims_HurtPlant[] = {
    ANIM_HurtPlant_Still,
    ANIM_HurtPlant_Hiding,
    ANIM_HurtPlant_Idle,
    ANIM_HurtPlant_Reveal,
    ANIM_LIST_END
};
