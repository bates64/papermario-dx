#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings AISettings_GoombaBros_Guard = {
    .alertRadius = 130.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 2.5f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
};

EvtScript EVS_NpcAI_GoombaBros_Guard = {
    Call(GuardAI_Main, Ref(AISettings_GoombaBros_Guard))
    Return
    End
};

NpcSettings NpcSettings_GoombaBros_Guard = {
    .height = 20,
    .radius = 23,
    .level = ACTOR_LEVEL_GOOMBA,
    .doAI = &EVS_NpcAI_GoombaBros_Guard,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
