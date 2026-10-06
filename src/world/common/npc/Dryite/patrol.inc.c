#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_Dryite_Patrol = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Dryite_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_Dryite_Patrol))
    Return
    End
};

NpcSettings NpcSettings_Dryite_Patrol = {
    .height = 26,
    .radius = 23,
    .doAI = &EVS_NpcAI_Dryite_Patrol,
    .level = ACTOR_LEVEL_NONE,
    .actionFlags = 16,
};
