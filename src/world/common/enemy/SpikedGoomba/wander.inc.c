#pragma once
#include "wander.h"

MobileAISettings AISettings_SpikedGoomba_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 130.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 2.5f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_SpikedGoomba_Wander = {
    Call(BasicAI_Main, Ref(AISettings_SpikedGoomba_Wander))
    Return
    End
};

NpcSettings NpcSettings_SpikedGoomba_Wander = {
    .height = 23,
    .radius = 23,
    .level = ACTOR_LEVEL_SPIKED_GOOMBA,
    .doAI = &EVS_NpcAI_SpikedGoomba_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
