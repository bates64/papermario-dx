#pragma once
#include "idle.h"

EvtScript EVS_NpcCreate_TrainToad_Idle = {
    Return
    End
};

NpcSettings NpcSettings_TrainToad = {
    .height = 32,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &EVS_NpcCreate_TrainToad_Idle,
};
