#pragma once
#include "wander.h"

#include "world/common/ai/FlyingNoAttackAI.inc.c"

MobileAISettings AISettings_RuffPuff_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 45,
    .waitTime = 60,
    .alertRadius = 100.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.6f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_RuffPuff_Wander = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, AI_FLYING_FLAG_INTERPY)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(6.0f))
    Call(FlyingNoAttackAI_Main, Ref(AISettings_RuffPuff_Wander))
    Return
    End
};

NpcSettings NpcSettings_RuffPuff_Wander = {
    .height = 24,
    .radius = 28,
    .level = ACTOR_LEVEL_RUFF_PUFF,
    .doAI = &EVS_NpcAI_RuffPuff_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
