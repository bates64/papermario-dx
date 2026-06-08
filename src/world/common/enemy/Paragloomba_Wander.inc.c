#include "Paragloomba.h"

#include "world/common/enemy/ai/FlyingAI.inc.c"

MobileAISettings N(AISettings_Paragloomba_Wander) = {
    .moveSpeed = 2.0f,
    .alertRadius = 80.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 2,
    .chaseRadius = 100.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Paragloomba_Wander) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, AI_FLYING_FLAG_INTERPY)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-8.5f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.6f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(6.0f))
    Call(N(FlyingAI_Main), Ref(N(AISettings_Paragloomba_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_Paragloomba_Wander) = {
    .height = 20,
    .radius = 21,
    .level = ACTOR_LEVEL_PARAGLOOMBA,
    .doAI = &N(EVS_NpcAI_Paragloomba_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
