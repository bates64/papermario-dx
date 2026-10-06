#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_SpikedGoomba_Patrol = {
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

EvtScript EVS_NpcAI_SpikedGoomba_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_SpikedGoomba_Patrol))
    Return
    End
};

NpcSettings NpcSettings_SpikedGoomba_Patrol = {
    .height = 23,
    .radius = 23,
    .level = ACTOR_LEVEL_SPIKED_GOOMBA,
    .doAI = &EVS_NpcAI_SpikedGoomba_Patrol,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
