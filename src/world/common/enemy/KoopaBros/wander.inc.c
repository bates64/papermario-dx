#pragma once
#include "wander.h"

MobileAISettings AISettings_KoopaBros = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_KoopaBros = {
    Call(BasicAI_Main, Ref(AISettings_KoopaBros))
    Return
    End
};

NpcSettings NpcSettings_KoopaBros = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_KoopaBros,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
