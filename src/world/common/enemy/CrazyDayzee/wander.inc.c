#pragma once
#include "wander.h"

MobileAISettings N(AISettings_CrazyDayzee_Wander) = {
    .moveSpeed = 1.0f,
    .moveTime = 500,
    .waitTime = 10,
    .alertRadius = 50.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 40,
    .chaseUpdateInterval = 3,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_CrazyDayzee_Wander) = {
    Call(BasicAI_Main, Ref(N(AISettings_CrazyDayzee_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_CrazyDayzee_Wander) = {
    .height = 30,
    .radius = 24,
    .level = ACTOR_LEVEL_CRAZEE_DAYZEE,
    .doAI = &N(EVS_NpcAI_CrazyDayzee_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
