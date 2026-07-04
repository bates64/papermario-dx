#pragma once
#include "idle.h"

NpcSettings N(NpcSettings_KoopaTroopa) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPA_TROOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
