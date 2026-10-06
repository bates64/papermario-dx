#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_Yoshi_Patrol = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Yoshi_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_Yoshi_Patrol))
    Return
    End
};

NpcSettings NpcSettings_Yoshi_Patrol = {
    .height = 48,
    .radius = 32,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Yoshi_Patrol,
};
