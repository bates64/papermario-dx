#pragma once
#include "wander.h"

#include "world/common/ai/FlyingAI.inc.c"

MobileAISettings AISettings_SkyGuy_Wander = {
    .moveSpeed = 1.8f,
    .alertRadius = 120.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_SkyGuy_Wander = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-6.5f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.3f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(6.0f))
    Call(FlyingAI_Main, Ref(AISettings_SkyGuy_Wander))
    Return
    End
};

NpcSettings NpcSettings_SkyGuy_Wander = {
    .height = 25,
    .radius = 22,
    .level = ACTOR_LEVEL_SKY_GUY,
    .doAI = &EVS_NpcAI_SkyGuy_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
