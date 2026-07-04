#pragma once
#include "idle.h"

EvtScript N(EVS_NpcCreate_TubbasHeart_Idle) = {
    Return
    End
};

EvtScript N(EVS_NpcDefeat_TubbasHeart_Idle) = {
    Return
    End
};

NpcSettings N(NpcSettings_TubbasHeart) = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_CLUBBA,
    .onCreate = &N(EVS_NpcCreate_TubbasHeart_Idle),
    .onDefeat = &N(EVS_NpcDefeat_TubbasHeart_Idle),
};
