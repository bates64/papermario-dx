#pragma once
#include "idle.h"

NpcSettings N(NpcSettings_RuffPuff) = {
    .height = 24,
    .radius = 28,
    .level = 16,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
