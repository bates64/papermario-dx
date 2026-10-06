#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_Duplighost_Patrol = {
    .moveSpeed = 2.0f,
    .alertRadius = 100.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 30,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Duplighost_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_Duplighost_Patrol))
    Return
    End
};

NpcSettings NpcSettings_Duplighost_Patrol = {
    .height = 30,
    .radius = 30,
    .level = ACTOR_LEVEL_DUPLIGHOST,
    .doAI = &EVS_NpcAI_Duplighost_Patrol,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
