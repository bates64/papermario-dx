#pragma once
#include "guard.h"

#include "world/common/ai/GuardAI.inc.c"

GuardAISettings N(AISettings_Kammy_Guard) = {
    .playerSearchInterval = -1,
    .chaseRadius = 300.0f,
};

EvtScript N(EVS_NpcAI_Kammy_Guard) = {
    Call(N(GuardAI_Main), Ref(N(AISettings_Kammy_Guard)))
    Return
    End
};

NpcSettings N(NpcSettings_Kammy_Guard) = {
    .height = 40,
    .radius = 30,
    .level = ACTOR_LEVEL_MAGIKOOPA,
    .doAI = &N(EVS_NpcAI_Kammy_Guard),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
