#include "Spiny.h"

#include "world/common/enemy/ai/TackleWanderAI.inc.c"

MobileAISettings N(AISettings_Spiny) = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 50,
    .alertRadius = 60.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 6.0f,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 3,
};

EvtScript N(EVS_NpcAI_Spiny) = {
    Call(SetSelfVar, AI_TACKLE_VAR_PRE_DELAY, 3)
    Call(SetSelfVar, AI_TACKLE_VAR_MIN_CHASE_TIME, 18)
    Call(SetSelfVar, AI_TACKLE_VAR_POST_DELAY, 3)
    Call(SetSelfVar, AI_TACKLE_VAR_TYPE, TACKLER_SPINY)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_Spiny)))
    Return
    End
};

NpcSettings N(NpcSettings_Spiny) = {
    .height = 21,
    .radius = 22,
    .level = ACTOR_LEVEL_SPINY,
    .doAI = &N(EVS_NpcAI_Spiny),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
