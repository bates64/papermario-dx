#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_Toad_Patrol = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Toad_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_Toad_Patrol))
    Return
    End
};

NpcSettings NpcSettings_Toad_Patrol = {
    .height = 30,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Toad_Patrol,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
