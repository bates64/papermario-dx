#pragma once
#include "idle.h"

NpcSettings NpcSettings_JungleFuzzy = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_JUNGLE_FUZZY,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
