#pragma once
#include "wander.h"

#include "world/common/ai/CleftAI.inc.c"

MobileAISettings AISettings_HyperCleft_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 120.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 8.5f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 3,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 60.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_HyperCleft_Wander = {
    Call(SetSelfVar, AI_VAR_CLEFT_DASH_DELAY, 8)
    Call(CleftAI_Main, Ref(AISettings_HyperCleft_Wander))
    Return
    End
};

NpcSettings NpcSettings_HyperCleft_Wander = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_HYPER_CLEFT,
    .doAI = &EVS_NpcAI_HyperCleft_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
