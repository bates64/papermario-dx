#include "Paratroopa.h"

#include "world/common/enemy/ai/ParatroopaAI.inc.c"

MobileAISettings N(AISettings_ParaTroopa) = {
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

EvtScript N(EVS_NpcAI_ParaTroopa) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(6))
    Call(N(ParatroopaAI_Main), Ref(N(AISettings_ParaTroopa)))
    Return
    End
};

NpcSettings N(NpcSettings_ParaTroopa) = {
    .height = 40,
    .radius = 24,
    .level = ACTOR_LEVEL_PARATROOPA,
    .doAI = &N(EVS_NpcAI_ParaTroopa),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
