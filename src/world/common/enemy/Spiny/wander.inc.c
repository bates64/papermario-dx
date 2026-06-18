#pragma once
#include "wander.h"

#include "world/common/ai/TackleWanderAI.inc.c"

MobileAISettings N(AISettings_Spiny_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 50,
    .alertRadius = 60.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 6.0f,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 3,
};

EvtScript N(EVS_NpcAI_Spiny_Wander) = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 3)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 18)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 3)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_SPINY)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_Spiny_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Spiny_Wander) = {
    .height = 21,
    .radius = 22,
    .level = ACTOR_LEVEL_SPINY,
    .doAI = &N(EVS_NpcAI_Spiny_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
