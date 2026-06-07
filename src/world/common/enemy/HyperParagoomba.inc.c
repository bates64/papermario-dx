#pragma once

#include "HyperParagoomba.h"

#include "world/common/enemy/ai/FlyingAI.inc.c"

MobileAISettings N(AISettings_HyperParagoomba) = {
    .moveSpeed = 1.8f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 120.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 5,
    .chaseUpdateInterval = 1,
    .chaseRadius = 150.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_HyperParagoomba) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, AI_FLYING_FLAG_INTERPY)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-8.5f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.6f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(7.0f))
    Call(N(FlyingAI_Main), Ref(N(AISettings_HyperParagoomba)))
    Return
    End
};

NpcSettings N(NpcSettings_HyperParagoomba) = {
    .height = 18,
    .radius = 20,
    .level = ACTOR_LEVEL_HYPER_GOOMBA,
    .doAI = &N(EVS_NpcAI_HyperParagoomba),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
