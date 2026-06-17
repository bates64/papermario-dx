#pragma once
#include "wander.h"

MobileAISettings N(AISettings_HyperGoomba_Wander) = {
    .moveSpeed = 1.8f,
    .moveTime = 40,
    .waitTime = 15,
    .alertRadius = 150.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 3.3f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 1,
    .chaseRadius = 180.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_HyperGoomba_Wander) = {
    Call(BasicAI_Main, Ref(N(AISettings_HyperGoomba_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_HyperGoomba_Wander) = {
    .height = 20,
    .radius = 23,
    .level = ACTOR_LEVEL_HYPER_GOOMBA,
    .doAI = &N(EVS_NpcAI_HyperGoomba_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
