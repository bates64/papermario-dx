#pragma once
#include "wander.h"

#include "world/common/ai/GrooveGuyAI.inc.c"

MobileAISettings N(AISettings_GrooveGuy_Wander) = {
    .moveSpeed = 1.7f,
    .moveTime = 80,
    .waitTime = 1,
    .alertRadius = 100.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 20,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_GrooveGuy_Wander) = {
    Call(N(GrooveGuyAI_Main), Ref(N(AISettings_GrooveGuy_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_GrooveGuy_Wander) = {
    .height = 24,
    .radius = 22,
    .level = ACTOR_LEVEL_GROOVE_GUY,
    .doAI = &N(EVS_NpcAI_GrooveGuy_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
