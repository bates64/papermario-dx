#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings AISettings_Bobomb_Guard = {
    .alertRadius = 110.0f,
    .alertOffsetDist = 65.0f,
    .playerSearchInterval = 8,
    .chaseSpeed = 3.4f,
    .chaseTurnRate = 120,
    .chaseUpdateInterval = 2,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 65.0f,
};

EvtScript EVS_NpcAI_Bobomb_Guard = {
    Call(GuardAI_Main, Ref(AISettings_Bobomb_Guard))
    Return
    End
};

NpcSettings NpcSettings_Bobomb_Guard = {
    .height = 23,
    .radius = 20,
    .level = ACTOR_LEVEL_BOB_OMB,
    .doAI = &EVS_NpcAI_Bobomb_Guard,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
