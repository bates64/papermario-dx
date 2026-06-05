#pragma once
#include "world/common/enemy/Clubba_Common.inc.c"
#include "world/common/enemy/ai/ClubbaNappingAI.inc.c"

MobileAISettings N(AISettings_Clubba_Napping) = {
    .moveSpeed = 1.0f,
    .moveTime = 120,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 15,
    .chaseRadius = 200.0f,
    .chaseOffsetDist = 160.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Clubba_Napping) = {
    Call(SetSelfVar, AI_VAR_MELEE_STATUS, MELEE_ATTACK_PHASE_NONE)
    Call(SetSelfVar, AI_VAR_MELEE_PRE_TIME, 10)
    Call(SetSelfVar, AI_VAR_MELEE_SWING_TIME, 14)
    Call(SetSelfVar, AI_VAR_MELEE_POST_TIME, 18)
    Call(N(ClubbaNappingAI_Main), Ref(N(AISettings_Clubba_Napping)))
    Return
    End
};

NpcSettings N(NpcSettings_Clubba_Napping) = {
    .height = 36,
    .radius = 34,
    .level = ACTOR_LEVEL_CLUBBA,
    .doAI = &N(EVS_NpcAI_Clubba_Napping),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
