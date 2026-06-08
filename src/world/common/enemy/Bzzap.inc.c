#include "Bzzap.h"

#include "world/common/enemy/ai/FlyingAI.inc.c"

MobileAISettings N(AISettings_Bzzap) = {
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

EvtScript N(EVS_NpcAI_Bzzap) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-6.3f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.5f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(2.0f))
    Call(N(FlyingAI_Main), Ref(N(AISettings_Bzzap)))
    Return
    End
};

NpcSettings N(NpcSettings_Bzzap) = {
    .height = 26,
    .radius = 24,
    .level = ACTOR_LEVEL_BZZAP,
    .doAI = &N(EVS_NpcAI_Bzzap),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
