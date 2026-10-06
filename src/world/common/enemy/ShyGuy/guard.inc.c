#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings AISettings_ShyGuy_Guard = {
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 6,
    .chaseUpdateInterval = 1,
    .chaseRadius = 160.0f,
    .chaseOffsetDist = 50.0f,
};

EvtScript EVS_NpcAI_ShyGuy_Guard = {
    Call(GuardAI_Main, Ref(AISettings_ShyGuy_Guard))
    Return
    End
};

NpcSettings NpcSettings_ShyGuy_Guard = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_SHY_GUY,
    .doAI = &EVS_NpcAI_ShyGuy_Guard,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
