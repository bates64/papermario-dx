#pragma once
#include "wander.h"

MobileAISettings AISettings_KoopaWithoutShell_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = -1,
};

EvtScript EVS_NpcAI_KoopaWithoutShell_Wander = {
    Call(BasicAI_Main, Ref(AISettings_KoopaWithoutShell_Wander))
    Return
    End
};

NpcSettings NpcSettings_KoopaWithoutShell_Wander = {
    .height = 36,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_KoopaWithoutShell_Wander,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
