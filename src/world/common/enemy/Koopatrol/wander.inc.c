#pragma once
#include "wander.h"

#include "world/common/ai/TackleWanderAI.inc.c"

MobileAISettings AISettings_Koopatrol_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 50,
    .alertRadius = 90.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 11.0f,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 40.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Koopatrol_Wander = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 5)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 4)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 10)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_KOOPATROL)
    Call(TackleWanderAI_Main, Ref(AISettings_Koopatrol_Wander))
    Return
    End
};

NpcSettings NpcSettings_Koopatrol_Wander = {
    .height = 40,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPATROL,
    .doAI = &EVS_NpcAI_Koopatrol_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
