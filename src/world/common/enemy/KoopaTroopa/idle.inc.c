#include "idle.h"
#include "base.h"

NpcSettings N(NpcSettings_KoopaTroopa_Stationary) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPA_TROOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
