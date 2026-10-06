#pragma once
#include "wander.h"

#include "world/common/ai/ParatroopaAI.inc.c"

MobileAISettings AISettings_ParaTroopa_Wander = {
    .moveSpeed = 2.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 20.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 2.6f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 10,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 20.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_ParaTroopa_Wander = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(6.0f))
    Call(ParatroopaAI_Main, Ref(AISettings_ParaTroopa_Wander))
    Return
    End
};

NpcSettings NpcSettings_ParaTroopa_Wander = {
    .height = 40,
    .radius = 24,
    .level = ACTOR_LEVEL_PARATROOPA,
    .doAI = &EVS_NpcAI_ParaTroopa_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
