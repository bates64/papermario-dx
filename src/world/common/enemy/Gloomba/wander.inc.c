#pragma once
#include "wander.h"

MobileAISettings AISettings_Gloomba_Wander = {
    .moveSpeed = 2.2f,
    .alertRadius = 70.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 3.2f,
    .chaseTurnRate = 15,
    .chaseUpdateInterval = 1,
    .chaseRadius = 90.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Gloomba_Wander = {
    Call(BasicAI_Main, Ref(AISettings_Gloomba_Wander))
    Return
    End
};

NpcSettings NpcSettings_Gloomba_Wander = {
    .height = 20,
    .radius = 23,
    .level = ACTOR_LEVEL_GLOOMBA,
    .doAI = &EVS_NpcAI_Gloomba_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
