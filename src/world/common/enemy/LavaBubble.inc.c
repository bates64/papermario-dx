#include "LavaBubble.h"

#include "world/common/enemy/ai/FlyingNoAttackAI.inc.c"

MobileAISettings N(AISettings_LavaBubble) = {
    .moveSpeed = 0.8f,
    .moveTime = 100,
    .alertRadius = 90.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 3.2f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 100.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_LavaBubble) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, AI_FLYING_FLAG_INTERPY)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(1.5f))
    Call(N(FlyingNoAttackAI_Main), Ref(N(AISettings_LavaBubble)))
    Return
    End
};

NpcSettings N(NpcSettings_LavaBubble) = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_LAVA_BUBBLE,
    .doAI = &N(EVS_NpcAI_LavaBubble),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
