#pragma once
#include "idle.h"

NpcSettings N(NpcSettings_GoombaFamily_Idle) = {
    .height = 22,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
