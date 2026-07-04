#pragma once
#include "wander.h"

MobileAISettings N(AISettings_KoopaBros) = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_KoopaBros) = {
    Call(BasicAI_Main, Ref(N(AISettings_KoopaBros)))
    Return
    End
};

NpcSettings N(NpcSettings_KoopaBros) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &N(EVS_NpcAI_KoopaBros),
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
