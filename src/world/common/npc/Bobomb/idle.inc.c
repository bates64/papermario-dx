#pragma once
#include "idle.h"
#include "base.h"

NpcSettings N(NpcSettings_Bobomb_Idle) = {
    .height = 23,
    .radius = 20,
    .level = ACTOR_LEVEL_BOB_OMB,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
