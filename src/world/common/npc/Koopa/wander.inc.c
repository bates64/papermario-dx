#pragma once
#include "wander.h"

MobileAISettings AISettings_Koopa_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Koopa_Wander = {
    Call(BasicAI_Main, Ref(AISettings_Koopa_Wander))
    Return
    End
};

NpcSettings NpcSettings_Koopa_Wander = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Koopa_Wander,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};

NpcSettings NpcSettings_TallKoopa_Wander = {
    .height = 42,
    .radius = 24,
    .doAI = &EVS_NpcAI_Koopa_Wander,
    .level = ACTOR_LEVEL_NONE,
};
