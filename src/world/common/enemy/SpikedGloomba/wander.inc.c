#pragma once
#include "wander.h"

MobileAISettings AISettings_SpikedGloomba_Wander = {
    .moveSpeed = 2.2f,
    .alertRadius = 70.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 3.2f,
    .chaseTurnRate = 15,
    .chaseUpdateInterval = 1,
    .chaseRadius = 90.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_SpikedGloomba_Wander = {
    Call(BasicAI_Main, Ref(AISettings_SpikedGloomba_Wander))
    Return
    End
};

NpcSettings NpcSettings_SpikedGloomba_Wander = {
    .height = 23,
    .radius = 23,
    .level = ACTOR_LEVEL_SPIKED_GLOOMBA,
    .doAI = &EVS_NpcAI_SpikedGloomba_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
