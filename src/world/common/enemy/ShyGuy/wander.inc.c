#pragma once
#include "wander.h"

#include "world/common/ai/ShyGuyWanderAI.inc.c"

MobileAISettings AISettings_ShyGuy_Wander = {
    .moveSpeed = 2.0f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 6,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_ShyGuy_Wander = {
    Call(ShyGuyWanderAI_Main, Ref(AISettings_ShyGuy_Wander))
    Return
    End
};

NpcSettings NpcSettings_ShyGuy_Wander = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_SHY_GUY,
    .doAI = &EVS_NpcAI_ShyGuy_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
