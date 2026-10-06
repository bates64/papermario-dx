#pragma once
#include "idle.h"

EvtScript EVS_NpcCreate_Bubulb_Idle = {
    Return
    End
};

NpcSettings NpcSettings_Bubulb = {
    .height = 42,
    .radius = 26,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &EVS_NpcCreate_Bubulb_Idle,
};
