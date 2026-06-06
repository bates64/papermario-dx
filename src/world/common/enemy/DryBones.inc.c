#include "DryBones.h"

#include "world/common/enemy/ai/WanderRangedAI.inc.c"

EvtScript N(EVS_NpcDefeat_ThrownBone) = {
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

MobileAISettings N(AISettings_DryBones) = {
    .moveSpeed = 2.0f,
    .moveTime = 20,
    .waitTime = 3,
    .alertRadius = 120.0f,
    .alertOffsetDist = 120.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 1.0f,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 150.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_DryBones) = {
    Call(SetSelfVar, AI_VAR_RANGED_MIN_DIST, 0)
    Call(SetSelfVar, AI_VAR_RANGED_PRE_TIME, 15)
    Call(SetSelfVar, AI_VAR_RANGED_POST_TIME, 10)
    Call(SetSelfVar, AI_VAR_RANGED_AMMO_COUNT, 2)
    Call(N(RangedAttackAI_Main), Ref(N(AISettings_DryBones)))
    Return
    End
};

NpcSettings N(NpcSettings_DryBones) = {
    .height = 32,
    .radius = 24,
    .level = ACTOR_LEVEL_DRY_BONES,
    .doAI = &N(EVS_NpcAI_DryBones),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

MobileAISettings N(AISettings_ThrownBone) = {
    .moveSpeed = 7.5f,
    .alertRadius = 1.1f,
    .alertOffsetDist = 0.18f,
    .playerSearchInterval = -1,
};

EvtScript N(EVS_NpcAI_ThrownBone) = {
    Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
    Call(SetSelfVar, AI_VAR_MISSILE_FLAGS, AI_MISSILE_FLAG_SPINNING | AI_MISSILE_FLAG_CENTERED)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_Y, 15)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_R, 15)
    Call(N(MissileAI_Main), Ref(N(AISettings_ThrownBone)))
    Return
    End
};

EvtScript N(EVS_NoAI_ThrownBone) = {
    Return
    End
};

EvtScript N(EVS_NpcHit_ThrownBone) = {
    Call(N(GetEncounterEnemyIsOwner))
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, NPC_SELF, Ref(N(EVS_NoAI_ThrownBone)))
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseOrEq(ENCOUNTER_TRIGGER_HAMMER)
        CaseOrEq(ENCOUNTER_TRIGGER_SPIN)
            Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_REFLECTING)
            Call(N(MissileAI_Reflect))
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
        EndCaseGroup
    EndSwitch
    Call(BindNpcAI, NPC_SELF, Ref(N(EVS_NpcAI_ThrownBone)))
    Return
    End
};

NpcSettings N(NpcSettings_ThrownBone) = {
    .height = 12,
    .radius = 12,
    .doAI = &N(EVS_NpcAI_ThrownBone),
    .onHit = &N(EVS_NpcHit_ThrownBone),
    .onDefeat = &N(EVS_NpcDefeat_ThrownBone),
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};
