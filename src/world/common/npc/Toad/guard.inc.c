#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings N(AISettings_Toad_Guard) = {
    .playerSearchInterval = -1,
    .chaseRadius = 300.0f,
};

EvtScript N(EVS_NpcAI_Toad_Guard) = {
    Call(N(GuardAI_Main), Ref(N(AISettings_Toad_Guard)))
    Return
    End
};

NpcSettings N(NpcSettings_Toad_Guard) = {
    .height = 30,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &N(EVS_NpcAI_Toad_Guard),
};
