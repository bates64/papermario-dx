#pragma once
#include "wander.h"

MobileAISettings AISettings_ToadKid_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_ToadKid_Wander = {
    Call(BasicAI_Main, Ref(AISettings_ToadKid_Wander))
    Return
    End
};

NpcSettings NpcSettings_ToadKid_Wander = {
    .height = 23,
    .radius = 19,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_ToadKid_Wander,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
