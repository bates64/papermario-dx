#pragma once
#include "wander.h"

MobileAISettings AISettings_Bobomb = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 10,
    .alertRadius = 110.0f,
    .alertOffsetDist = 65.0f,
    .playerSearchInterval = 8,
    .chaseSpeed = 3.4f,
    .chaseTurnRate = 120,
    .chaseUpdateInterval = 2,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 65.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Bobomb_Wander = {
    Call(BasicAI_Main, Ref(AISettings_Bobomb))
    Return
    End
};

NpcSettings NpcSettings_Bobomb_Wander = {
    .height = 23,
    .radius = 20,
    .level = ACTOR_LEVEL_BOB_OMB,
    .doAI = &EVS_NpcAI_Bobomb_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
