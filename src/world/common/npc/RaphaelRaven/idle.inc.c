#pragma once
#include "idle.h"

EvtScript EVS_NpcCreate_RaphaelRaven_Idle = {
    Call(SetNpcScale, NPC_SELF, 1.5, 1.5, 1.5)
    Return
    End
};

NpcSettings NpcSettings_RaphaelRaven = {
    .height = 98,
    .radius = 80,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &EVS_NpcCreate_RaphaelRaven_Idle,
};
