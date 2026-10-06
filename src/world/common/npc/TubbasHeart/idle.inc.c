#pragma once
#include "idle.h"

EvtScript EVS_NpcCreate_TubbasHeart_Idle = {
    Return
    End
};

EvtScript EVS_NpcDefeat_TubbasHeart_Idle = {
    Return
    End
};

NpcSettings NpcSettings_TubbasHeart = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_CLUBBA,
    .onCreate = &EVS_NpcCreate_TubbasHeart_Idle,
    .onDefeat = &EVS_NpcDefeat_TubbasHeart_Idle,
};
