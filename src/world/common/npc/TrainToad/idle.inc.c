#pragma once
#include "idle.h"

EvtScript N(EVS_NpcCreate_TrainToad_Idle) = {
    Return
    End
};

NpcSettings N(NpcSettings_TrainToad) = {
    .height = 32,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_TrainToad_Idle),
};
