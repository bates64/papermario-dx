#pragma once
#include "wander.h"

#include "world/common/ai/WanderRangedAI.inc.c"

EvtScript EVS_NpcDefeat_HammerBros_Hammer = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_DONE)
            Call(RemoveNpc, NPC_SELF)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            Call(OnPlayerFled, true)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

MobileAISettings AISettings_HammerBros = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 120.0f,
    .alertOffsetDist = 20.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 3,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 20.0f,
};

EvtScript EVS_NpcAI_HammerBros = {
    Call(SetSelfVar, AI_VAR_RANGED_MIN_DIST, 70)
    Call(SetSelfVar, AI_VAR_RANGED_PRE_TIME, 3)
    Call(SetSelfVar, AI_VAR_RANGED_POST_TIME, 3)
    Call(SetSelfVar, AI_VAR_RANGED_AMMO_COUNT, 6)
    Call(RangedAttackAI_Main, Ref(AISettings_HammerBros))
    Return
    End
};

NpcSettings NpcSettings_HammerBros_Wander = {
    .height = 36,
    .radius = 24,
    .level = ACTOR_LEVEL_HAMMER_BROS,
    .doAI = &EVS_NpcAI_HammerBros,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

MobileAISettings AISettings_HammerBros_Hammer = {
    .moveSpeed = 5.4f,
    .alertRadius = 13.0f,
    .alertOffsetDist = 1.4f,
    .playerSearchInterval = -1,
};

EvtScript EVS_NpcAI_HammerBros_Hammer = {
    Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
    Call(SetSelfVar, AI_VAR_MISSILE_FLAGS, AI_MISSILE_FLAG_SPINNING | AI_MISSILE_FLAG_CENTERED)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_Y, 20)
    Call(MissileAI_Main, Ref(AISettings_HammerBros_Hammer))
    Return
    End
};

EvtScript EVS_NoAI_HammerBros_Hammer = {
    Return
    End
};

EvtScript EVS_NpcHit_HammerBros_Hammer = {
    Call(GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NoAI_HammerBros_Hammer))
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseOrEq(ENCOUNTER_TRIGGER_HAMMER)
        CaseOrEq(ENCOUNTER_TRIGGER_SPIN)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_REFLECTING)
            Call(MissileAI_Reflect)
            IfEq(LVar0, 0)
                Return
            EndIf
        EndCaseGroup
        CaseOrEq(ENCOUNTER_TRIGGER_JUMP)
        CaseOrEq(ENCOUNTER_TRIGGER_PARTNER)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_DESTROYED)
            Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
            PlayEffect(EFFECT_WALKING_DUST, 2, LVar0, LVar1, LVar2, 0, 0)
            Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
        EndCaseGroup
        CaseDefault
            Call(SetBattleAsScripted)
    EndSwitch
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_HammerBros_Hammer))
    Return
    End
};

NpcSettings NpcSettings_HammerBros_Hammer = {
    .height = 12,
    .radius = 12,
    .doAI = &EVS_NpcAI_HammerBros_Hammer,
    .onHit = &EVS_NpcHit_HammerBros_Hammer,
    .onDefeat = &EVS_NpcDefeat_HammerBros_Hammer,
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};

AnimID LimitAnims_HammerBros_Hammer[] = {
    ANIM_HammerBros_Hammer,
    ANIM_LIST_END
};
