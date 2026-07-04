#pragma once
#include "idle.h"

NpcSettings N(NpcSettings_Magikoopa) = {
    .height = 34,
    .radius = 24,
    .level = ACTOR_LEVEL_MAGIKOOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
