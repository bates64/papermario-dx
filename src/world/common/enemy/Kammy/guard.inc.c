#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings AISettings_Kammy_Guard = {
    .playerSearchInterval = -1,
    .chaseRadius = 300.0f,
};

EvtScript EVS_NpcAI_Kammy_Guard = {
    Call(GuardAI_Main, Ref(AISettings_Kammy_Guard))
    Return
    End
};

NpcSettings NpcSettings_Kammy_Guard = {
    .height = 40,
    .radius = 30,
    .level = ACTOR_LEVEL_MAGIKOOPA,
    .doAI = &EVS_NpcAI_Kammy_Guard,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
