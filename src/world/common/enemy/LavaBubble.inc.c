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
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 150)
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
