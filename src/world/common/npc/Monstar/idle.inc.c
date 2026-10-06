#pragma once
#include "idle.h"

NpcSettings NpcSettings_Monstar = {
    .height = 150,
    .radius = 150,
    .level = ACTOR_LEVEL_NONE,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
