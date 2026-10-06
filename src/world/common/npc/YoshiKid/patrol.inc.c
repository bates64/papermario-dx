#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_YoshiKid_Patrol = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_YoshiKid_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_YoshiKid_Patrol))
    Return
    End
};

NpcSettings NpcSettings_YoshiKid_Patrol = {
    .height = 28,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_YoshiKid_Patrol,
};
