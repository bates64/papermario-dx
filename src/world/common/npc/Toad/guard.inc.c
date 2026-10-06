#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings AISettings_Toad_Guard = {
    .playerSearchInterval = -1,
    .chaseRadius = 300.0f,
};

EvtScript EVS_NpcAI_Toad_Guard = {
    Call(GuardAI_Main, Ref(AISettings_Toad_Guard))
    Return
    End
};

NpcSettings NpcSettings_Toad_Guard = {
    .height = 30,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_Toad_Guard,
};
