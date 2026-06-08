#include "RuffPuff.h"

#include "world/common/enemy/ai/FlyingNoAttackAI.inc.c"

MobileAISettings N(AISettings_RuffPuff) = {
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

EvtScript N(EVS_NpcAI_RuffPuff) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, AI_FLYING_FLAG_INTERPY)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(6.0f))
    Call(N(FlyingNoAttackAI_Main), Ref(N(AISettings_RuffPuff)))
    Return
    End
};

NpcSettings N(NpcSettings_RuffPuff) = {
    .height = 24,
    .radius = 28,
    .level = ACTOR_LEVEL_RUFF_PUFF,
    .doAI = &N(EVS_NpcAI_RuffPuff),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
