#pragma once
#include "world/common/enemy/FrostClubba_Common.inc.c"
#include "world/common/enemy/ai/ClubbaPatrolAI.inc.c"

MobileAISettings N(AISettings_FrostClubba_Patrol) = {
    .moveSpeed = 2.0f,
    .alertRadius = 100.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 7,
    .chaseSpeed = 3.8f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 10,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 50.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_FrostClubba_Patrol) = {
    Call(SetSelfVar, AI_VAR_MELEE_STATUS, MELEE_ATTACK_PHASE_NONE)
    Call(SetSelfVar, AI_VAR_MELEE_PRE_TIME, 3)
    Call(SetSelfVar, AI_VAR_MELEE_SWING_TIME, 7)
    Call(SetSelfVar, AI_VAR_MELEE_POST_TIME, 6)
    Call(N(ClubbaPatrolAI_Main), Ref(N(AISettings_FrostClubba_Patrol)))
    Return
    End
};

NpcSettings N(NpcSettings_FrostClubba_Patrol) = {
    .height = 36,
    .radius = 34,
    .level = ACTOR_LEVEL_WHITE_CLUBBA,
    .doAI = &N(EVS_NpcAI_FrostClubba_Patrol),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
