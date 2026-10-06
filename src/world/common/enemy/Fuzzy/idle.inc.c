#pragma once
#include "idle.h"

NpcSettings NpcSettings_Fuzzy = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_FUZZY,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
