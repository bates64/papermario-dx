#include "HammerBros.h"

#include "world/common/enemy/ai/WanderRangedAI.inc.c"

EvtScript N(EVS_NpcDefeat_HammerBros_Hammer) = {
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

MobileAISettings N(AISettings_HammerBros) = {
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

EvtScript N(EVS_NpcAI_HammerBros) = {
    Call(SetSelfVar, AI_VAR_RANGED_MIN_DIST, 70)
    Call(SetSelfVar, AI_VAR_RANGED_PRE_TIME, 3)
    Call(SetSelfVar, AI_VAR_RANGED_POST_TIME, 3)
    Call(SetSelfVar, AI_VAR_RANGED_AMMO_COUNT, 6)
    Call(N(RangedAttackAI_Main), Ref(N(AISettings_HammerBros)))
    Return
    End
};

NpcSettings N(NpcSettings_HammerBros_Wander) = {
    .height = 36,
    .radius = 24,
    .level = ACTOR_LEVEL_HAMMER_BROS,
    .doAI = &N(EVS_NpcAI_HammerBros),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

MobileAISettings N(AISettings_HammerBros_Hammer) = {
    .moveSpeed = 5.4f,
    .alertRadius = 13.0f,
    .alertOffsetDist = 1.4f,
    .playerSearchInterval = -1,
};

EvtScript N(EVS_NpcAI_HammerBros_Hammer) = {
    Call(SetSelfVar, AI_VAR_MISSILE_STATUS, MISSILE_STATUS_IDLE)
    Call(SetSelfVar, AI_VAR_MISSILE_FLAGS, AI_MISSILE_FLAG_SPINNING | AI_MISSILE_FLAG_CENTERED)
    Call(SetSelfVar, AI_VAR_MISSILE_SPAWN_Y, 20)
    Call(N(MissileAI_Main), Ref(N(AISettings_HammerBros_Hammer)))
    Return
    End
};

EvtScript N(EVS_NoAI_HammerBros_Hammer) = {
    Return
    End
};

EvtScript N(EVS_NpcHit_HammerBros_Hammer) = {
    Call(N(GetEncounterEnemyIsOwner))
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, NPC_SELF, Ref(N(EVS_NoAI_HammerBros_Hammer)))
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
    Call(BindNpcAI, NPC_SELF, Ref(N(EVS_NpcAI_HammerBros_Hammer)))
    Return
    End
};

NpcSettings N(NpcSettings_HammerBros_Hammer) = {
    .height = 12,
    .radius = 12,
    .doAI = &N(EVS_NpcAI_HammerBros_Hammer),
    .onHit = &N(EVS_NpcHit_HammerBros_Hammer),
    .onDefeat = &N(EVS_NpcDefeat_HammerBros_Hammer),
    .actionFlags = AI_ACTION_NO_SPIN_REACTION,
};

AnimID N(ExtraAnims_HammerBros_Hammer)[] = {
    ANIM_HammerBros_Anim0D,
    ANIM_LIST_END
};
