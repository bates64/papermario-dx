#pragma once
#include "wander.h"

MobileAISettings AISettings_GoombaFamily_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_GoombaFamily_Wander = {
    Call(BasicAI_Main, Ref(AISettings_GoombaFamily_Wander))
    Return
    End
};

NpcSettings NpcSettings_GoombaFamily_Wander = {
    .height = 22,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_GoombaFamily_Wander,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
