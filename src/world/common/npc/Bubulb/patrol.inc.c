#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_Bubulb_Patrol = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Bubulb_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_Bubulb_Patrol))
    Return
    End
};

NpcSettings NpcSettings_Bubulb_Patrol = {
    .height = 42,
    .radius = 28,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Bubulb_Patrol,
};
