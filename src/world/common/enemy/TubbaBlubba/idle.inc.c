#pragma once
#include "idle.h"

NpcSettings NpcSettings_TubbaBlubba = {
    .height = 90,
    .radius = 65,
    .level = ACTOR_LEVEL_CLUBBA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
