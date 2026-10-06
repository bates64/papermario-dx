#pragma once
#include "idle.h"

NpcSettings NpcSettings_Kammy = {
    .height = 40,
    .radius = 30,
    .level = ACTOR_LEVEL_MAGIKOOPA,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
