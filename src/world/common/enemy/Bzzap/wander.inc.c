#pragma once
#include "wander.h"

#include "world/common/ai/FlyingAI.inc.c"

MobileAISettings AISettings_Bzzap_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 5,
    .alertRadius = 80.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 6,
    .chaseUpdateInterval = 1,
    .chaseRadius = 90.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Bzzap_Wander = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-6.3f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.5f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(2.0f))
    Call(FlyingAI_Main, Ref(AISettings_Bzzap_Wander))
    Return
    End
};

NpcSettings NpcSettings_Bzzap_Wander = {
    .height = 26,
    .radius = 24,
    .level = ACTOR_LEVEL_BZZAP,
    .doAI = &EVS_NpcAI_Bzzap_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
