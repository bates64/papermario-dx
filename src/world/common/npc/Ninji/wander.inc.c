#pragma once
#include "wander.h"

MobileAISettings AISettings_Ninji_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Ninji_Wander = {
    Call(BasicAI_Main, Ref(AISettings_Ninji_Wander))
    Return
    End
};

NpcSettings NpcSettings_Ninji_Wander = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Ninji_Wander,
};
