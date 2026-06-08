#include "KoopaTroopa.h"

#include "world/common/enemy/ai/TacklePatrolAI.inc.c"

MobileAISettings N(AISettings_KoopaTroopa_Patrol) = {
    .moveSpeed = 1.5f,
    .moveTime = 25,
    .waitTime = 20,
    .alertRadius = 70.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 7.0f,
    .chaseRadius = 80.0f,
    .chaseOffsetDist = 60.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_KoopaTroopa_Patrol) = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 8)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 12)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 10)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_KOOPATROL)
    Call(N(TacklePatrolAI_Main), Ref(N(AISettings_KoopaTroopa_Patrol)))
    Return
    End
};

NpcSettings N(NpcSettings_KoopaTroopa_Patrol) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_KOOPA_TROOPA,
    .doAI = &N(EVS_NpcAI_KoopaTroopa_Patrol),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
