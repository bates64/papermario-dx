#pragma once
#include "idle.h"
#include "world/common/npc/Kooper/base.h"

NpcSettings N(NpcSettings_Koopa) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};
