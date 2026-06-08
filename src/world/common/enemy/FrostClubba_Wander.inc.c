#pragma once
#include "world/common/enemy/FrostClubba_Common.inc.c"
#include "world/common/enemy/ai/WanderMeleeAI.inc.c"

MobileAISettings N(AISettings_FrostClubba_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 120,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 7,
    .chaseSpeed = 3.8f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 15,
    .chaseRadius = 200.0f,
    .chaseOffsetDist = 160.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_FrostClubba_Wander) = {
    Call(SetSelfVar, AI_VAR_MELEE_STATUS, MELEE_ATTACK_PHASE_NONE)
    Call(SetSelfVar, AI_VAR_MELEE_PRE_TIME, 3)
    Call(SetSelfVar, AI_VAR_MELEE_SWING_TIME, 7)
    Call(SetSelfVar, AI_VAR_MELEE_POST_TIME, 6)
    Call(N(WanderMeleeAI_Main), Ref(N(AISettings_FrostClubba_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_FrostClubba_Wander) = {
    .height = 36,
    .radius = 34,
    .level = ACTOR_LEVEL_WHITE_CLUBBA,
    .doAI = &N(EVS_NpcAI_FrostClubba_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
