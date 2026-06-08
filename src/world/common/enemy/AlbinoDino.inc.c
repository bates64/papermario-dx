#pragma once
#include "AlbinoDino.h"

EvtScript N(EVS_NpcCreate_AlbinoDino) = {
    Return
    End
};

NpcSettings N(NpcSettings_AlbinoDino) = {
    .height = 70,
    .radius = 50,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_AlbinoDino),
    .onDefeat = &EnemyNpcDefeat,
};
