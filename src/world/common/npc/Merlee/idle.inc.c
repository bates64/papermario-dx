#pragma once
#include "idle.h"

EvtScript N(EVS_NpcInit_Merlee_Idle) = {
    Return
    End
};

NpcSettings N(NpcSettings_Merlee_Idle) = {
    .height = 32,
    .radius = 32,
    .onInteract = &N(EVS_NpcInteract_Merlee),
    .level = ACTOR_LEVEL_NONE,
};
