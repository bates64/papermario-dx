#pragma once
#include "idle.h"

NpcSettings NpcSettings_YMagikoopa = {
    .height = 34,
    .radius = 24,
    .level = ACTOR_LEVEL_YELLOW_MAGIKOOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
