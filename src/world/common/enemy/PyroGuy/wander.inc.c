#pragma once
#include "wander.h"

MobileAISettings N(AISettings_PyroGuy_Wander) = {
    .moveSpeed = 3.0f,
    .moveTime = 30,
    .waitTime = 60,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 5.0f,
    .chaseTurnRate = 8,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_PyroGuy_Wander) = {
    Call(BasicAI_Main, Ref(N(AISettings_PyroGuy_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_PyroGuy_Wander) = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_PYRO_GUY,
    .doAI = &N(EVS_NpcAI_PyroGuy_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
