#pragma once
#include "idle.h"

EvtScript EVS_NpcCreate_AlbinoDino = {
    Return
    End
};

NpcSettings NpcSettings_AlbinoDino = {
    .height = 70,
    .radius = 50,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &EVS_NpcCreate_AlbinoDino,
    .onDefeat = &EnemyNpcDefeat,
};
