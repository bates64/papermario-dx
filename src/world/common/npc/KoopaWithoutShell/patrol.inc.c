#pragma once
#include "patrol.h"

#include "world/common/ai/PatrolNoAttackAI.inc.c"

MobileAISettings AISettings_KoopaWithoutShell_Patrol = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_KoopaWithoutShell_Patrol = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_KoopaWithoutShell_Patrol))
    Return
    End
};

NpcSettings NpcSettings_KoopaWithoutShell_Patrol = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_KoopaWithoutShell_Patrol,
    .actionFlags = AI_ACTION_LOOK_AROUND_DURING_LOITER,
};

NpcSettings missing_80246F94_6F94 = {
    .height = 42,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &EVS_NpcAI_KoopaWithoutShell_Patrol,
};
