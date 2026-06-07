#include "Paragoomba.h"

#include "world/common/enemy/ai/FlyingAI.inc.c"

MobileAISettings N(AISettings_Paragoomba_Wander) = {
    .moveSpeed = 1.6f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 80.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 2.2f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 15,
    .chaseRadius = 100.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Paragoomba_Wander) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-5.0f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.21f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(5.8f))
    Call(N(FlyingAI_Main), Ref(N(AISettings_Paragoomba_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Paragoomba_Wander) = {
    .height = 20,
    .radius = 21,
    .level = ACTOR_LEVEL_PARAGOOMBA,
    .doAI = &N(EVS_NpcAI_Paragoomba_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_NO_FIRST_STRIKE,
};
