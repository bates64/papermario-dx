#pragma once
#include "wander.h"

NpcSettings N(NpcSettings_FlyingMagikoopa) = {
    .height = 34,
    .radius = 24,
    .level = ACTOR_LEVEL_MAGIKOOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
