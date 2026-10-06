#pragma once
#include "wander.h"

#include "world/common/ai/WanderRangedAI.inc.c"

API_CALLABLE(SetSpyGuyInstigatorValue) {
    script->owner1.enemy->instigatorValue = 3;
    return ApiStatus_DONE2;
}

EvtScript EVS_NpcDefeat_SpyGuyRock = {
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

MobileAISettings AISettings_SpyGuy_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 90.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.8f,
    .chaseTurnRate = 8,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 60.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_SpyGuy_Wander = {
    Call(SetSpyGuyInstigatorValue)
    Call(SetSelfVar, AI_VAR_RANGED_MIN_DIST, 0)
    Call(SetSelfVar, AI_VAR_RANGED_PRE_TIME, 12)
    Call(SetSelfVar, AI_VAR_RANGED_POST_TIME, 5)
    Call(SetSelfVar, AI_VAR_RANGED_AMMO_COUNT, 2)
    Call(RangedAttackAI_Main, Ref(AISettings_SpyGuy_Wander))
    Return
    End
};

NpcSettings NpcSettings_SpyGuy_Wander = {
    .height = 24,
    .radius = 22,
    .level = ACTOR_LEVEL_SPY_GUY,
    .doAI = &EVS_NpcAI_SpyGuy_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

MobileAISettings AISettings_SpyGuyRock = {
    .moveSpeed = 8.0f,
    .alertRadius = 4.0f,
    .alertOffsetDist = 0.5f,
    .playerSearchInterval = -1,
};

EvtScript EVS_NpcAI_SpyGuyRock = {
    Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
    Call(SetSelfVar, AI_VAR_MISSILE_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_Y, 12)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_R, 13)
    Call(MissileAI_Main, Ref(AISettings_SpyGuyRock))
    Return
    End
};

EvtScript EVS_NoAI_SpyGuyRock = {
    Return
    End
};

EvtScript EVS_NpcHit_SpyGuyRock = {
    Call(GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NoAI_SpyGuyRock))
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
    Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_SpyGuyRock))
    Return
    End
};

NpcSettings NpcSettings_SpyGuyRock = {
    .height = 7,
    .radius = 7,
    .doAI = &EVS_NpcAI_SpyGuyRock,
    .onHit = &EVS_NpcHit_SpyGuyRock,
    .onDefeat = &EVS_NpcDefeat_SpyGuyRock,
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};
