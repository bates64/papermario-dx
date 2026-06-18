#pragma once
#include "wander.h"

#include "world/common/ai/CleftAI.inc.c"

MobileAISettings N(AISettings_Cleft_Wander) = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 120.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 7.0f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 5,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 60.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Cleft_Wander) = {
    Call(SetSelfVar, AI_VAR_CLEFT_DASH_DELAY, 16)
    Call(N(CleftAI_Main), Ref(N(AISettings_Cleft_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Cleft_Wander) = {
    .height = 26,
    .radius = 24,
    .level = ACTOR_LEVEL_CLEFT,
    .doAI = &N(EVS_NpcAI_Cleft_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
