#pragma once
#include "idle.h"

EvtScript N(EVS_NpcCreate_Bubulb_Idle) = {
    Return
    End
};

NpcSettings N(NpcSettings_Bubulb) = {
    .height = 42,
    .radius = 26,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_Bubulb_Idle),
};
