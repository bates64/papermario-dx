#pragma once
#include "wander.h"

MobileAISettings N(AISettings_Ninji_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Ninji_Wander) = {
    Call(BasicAI_Main, Ref(N(AISettings_Ninji_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Ninji_Wander) = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &N(EVS_NpcAI_Ninji_Wander),
};
