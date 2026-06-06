#include "KoopaTroopa.h"

#include "world/common/enemy/ai/TackleWanderAI.inc.c"

MobileAISettings N(AISettings_KoopaTroopa_Wander) = {
    .moveSpeed = 1.5f,
    .moveTime = 45,
    .waitTime = 20,
    .alertRadius = 70.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 7.5f,
    .chaseRadius = 80.0f,
    .chaseOffsetDist = 60.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_KoopaTroopa_Wander) = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 8)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 12)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 10)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_KOOPA_TROOPA)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_KoopaTroopa_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_KoopaTroopa_Wander) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPA_TROOPA,
    .doAI = &N(EVS_NpcAI_KoopaTroopa_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
