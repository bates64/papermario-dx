#pragma once
#include "wander.h"

MobileAISettings AISettings_Dryite_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Dryite_Wander = {
    Call(BasicAI_Main, Ref(AISettings_Dryite_Wander))
    Return
    End
};

NpcSettings NpcSettings_Dryite_Wander = {
    .height = 26,
    .radius = 23,
    .doAI = &EVS_NpcAI_Dryite_Wander,
    .level = ACTOR_LEVEL_NONE,
    .actionFlags = 16,
};
