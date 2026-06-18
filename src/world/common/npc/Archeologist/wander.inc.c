#pragma once
#include "wander.h"

MobileAISettings N(AISettings_Archeologist_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Archeologist_Wander) = {
    Call(BasicAI_Main, Ref(N(AISettings_Archeologist_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Archeologist_Wander) = {
    .height = 42,
    .radius = 24,
    .doAI = &N(EVS_NpcAI_Archeologist_Wander),
    .level = ACTOR_LEVEL_NONE,
};
