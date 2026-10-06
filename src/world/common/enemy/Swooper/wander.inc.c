#pragma once
#include "wander.h"

#include "world/common/ai/SwooperAI.inc.c"

MobileAISettings AISettings_Swooper_Wander = {
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

EvtScript EVS_NpcAI_Swooper_Wander = {
    Call(SwooperAI_Main, Ref(AISettings_Swooper_Wander))
    Return
    End
};

MobileAISettings AISettings_Swoopula_Wander = {
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

EvtScript EVS_NpcAI_Swoopula_Wander = {
    Call(SwooperAI_Main, Ref(AISettings_Swoopula_Wander))
    Return
    End
};

NpcSettings NpcSettings_Swooper_Wander = {
    .height = 20,
    .radius = 20,
    .level = ACTOR_LEVEL_SWOOPER,
    .doAI = &EVS_NpcAI_Swooper_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .flags = ENEMY_FLAG_FLYING,
};

NpcSettings NpcSettings_Swoopula_Wander = {
    .height = 20,
    .radius = 20,
    .level = ACTOR_LEVEL_SWOOPULA,
    .doAI = &EVS_NpcAI_Swoopula_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .flags = ENEMY_FLAG_FLYING,
};
