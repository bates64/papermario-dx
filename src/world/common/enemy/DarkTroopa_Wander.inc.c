#include "common.h"
#include "DarkTroopa.h"

#include "world/common/enemy/ai/TackleWanderAI.inc.c"

MobileAISettings N(AISettings_DarkTroopa_Wander) = {
    .moveSpeed = 2.0f,
    .moveTime = 60,
    .waitTime = 5,
    .alertRadius = 80.0f,
    .alertOffsetDist = 60.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 9.0f,
    .chaseRadius = 90.0f,
    .chaseOffsetDist = 70.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_DarkTroopa_Wander) = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 6)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 4)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 13)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_DARK_TROOPA)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_DarkTroopa_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_DarkTroopa_Wander) = {
    .height = 35,
    .radius = 24,
    .level = ACTOR_LEVEL_DARK_KOOPA,
    .doAI = &N(EVS_NpcAI_DarkTroopa_Wander),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
