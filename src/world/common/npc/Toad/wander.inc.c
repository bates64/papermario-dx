#pragma once
#include "wander.h"

MobileAISettings AISettings_Toad_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Toad_Wander = {
    Call(BasicAI_Main, Ref(AISettings_Toad_Wander))
    Return
    End
};

NpcSettings NpcSettings_Toad_Wander = {
    .height = 30,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Toad_Wander,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
