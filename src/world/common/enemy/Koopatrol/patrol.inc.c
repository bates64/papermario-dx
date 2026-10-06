#pragma once
#include "patrol.h"

#include "world/common/ai/TacklePatrolAI.inc.c"

MobileAISettings AISettings_Koopatrol_Patrol = {
    .moveSpeed = 1.0f,
    .moveTime = 34,
    .waitTime = 50,
    .alertRadius = 90.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 11.0f,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 60.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Koopatrol_Patrol = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 8)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 15)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 10)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_KOOPATROL)
    Call(TacklePatrolAI_Main, Ref(AISettings_Koopatrol_Patrol))
    Return
    End
};

NpcSettings NpcSettings_Koopatrol_Patrol = {
    .height = 40,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPATROL,
    .doAI = &EVS_NpcAI_Koopatrol_Patrol,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
