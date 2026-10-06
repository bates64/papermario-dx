#pragma once
#include "idle.h"

EvtScript EVS_NpcCreate_StarRod_Idle = {
    Return
    End
};

NpcSettings NpcSettings_StarRod = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &EVS_NpcCreate_StarRod_Idle,
};
