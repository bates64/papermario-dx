#pragma once
#include "idle.h"
#include "base.h"

EvtScript N(EVS_NpcCreate_Bubulb_Idle) = {
    Return
    End
};

NpcSettings N(NpcSettings_Bubulb_Idle) = {
    .height = 42,
    .radius = 26,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_Bubulb_Idle),
};
