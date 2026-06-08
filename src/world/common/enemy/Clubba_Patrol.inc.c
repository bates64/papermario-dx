#pragma once
#include "world/common/enemy/Clubba_Common.inc.c"
#include "world/common/enemy/ai/ClubbaPatrolAI.inc.c"

MobileAISettings N(AISettings_Clubba_Patrol) = {
    .moveSpeed = 1.5f,
    .moveTime = 20,
    .waitTime = 30,
    .alertRadius = 85.0f,
    .alertOffsetDist = 65.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 12,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 90.0f,
    .loiterMode = 3,
};

EvtScript N(EVS_NpcAI_Clubba_Patrol) = {
    Call(SetSelfVar, AI_VAR_MELEE_STATUS, MELEE_ATTACK_PHASE_NONE)
    Call(SetSelfVar, AI_VAR_MELEE_PRE_TIME, 5)
    Call(SetSelfVar, AI_VAR_MELEE_SWING_TIME, 8)
    Call(SetSelfVar, AI_VAR_MELEE_POST_TIME, 12)
    Call(N(ClubbaPatrolAI_Main), Ref(N(AISettings_Clubba_Patrol)))
    Return
    End
};

NpcSettings N(NpcSettings_Clubba_Patrol) = {
    .height = 36,
    .radius = 34,
    .level = ACTOR_LEVEL_CLUBBA,
    .doAI = &N(EVS_NpcAI_Clubba_Patrol),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
