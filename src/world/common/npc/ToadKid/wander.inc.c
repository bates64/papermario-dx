#pragma once
#include "wander.h"

MobileAISettings N(AISettings_ToadKid_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_ToadKid_Wander) = {
    Call(BasicAI_Main, Ref(N(AISettings_ToadKid_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_ToadKid_Wander) = {
    .height = 23,
    .radius = 19,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &N(EVS_NpcAI_ToadKid_Wander),
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
