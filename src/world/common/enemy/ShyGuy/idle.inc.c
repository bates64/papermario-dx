#pragma once
#include "idle.h"

NpcSettings N(NpcSettings_ShyGuy) = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_SHY_GUY,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
