#pragma once
#include "wander.h"

#include "world/common/ai/SwooperAI.inc.c"

MobileAISettings N(AISettings_Swooper_Wander) = {
    .moveSpeed = 1.6f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 80.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 2.2f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 15,
    .chaseRadius = 100.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Swooper_Wander) = {
    Call(N(SwooperAI_Main), Ref(N(AISettings_Swooper_Wander)))
    Return
    End
};

MobileAISettings N(AISettings_Swoopula_Wander) = {
    .moveSpeed = 1.6f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 80.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 2.2f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 15,
    .chaseRadius = 100.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Swoopula_Wander) = {
    Call(N(SwooperAI_Main), Ref(N(AISettings_Swoopula_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Swooper_Wander) = {
    .height = 20,
    .radius = 20,
    .level = ACTOR_LEVEL_SWOOPER,
    .doAI = &N(EVS_NpcAI_Swooper_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .flags = ENEMY_FLAG_FLYING,
};

NpcSettings N(NpcSettings_Swoopula_Wander) = {
    .height = 20,
    .radius = 20,
    .level = ACTOR_LEVEL_SWOOPULA,
    .doAI = &N(EVS_NpcAI_Swoopula_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .flags = ENEMY_FLAG_FLYING,
};
