#include "SpikeTop.h"

#include "world/common/enemy/ai/TackleWanderAI.inc.c"

MobileAISettings N(AISettings_BuzzyBeetle) = {
    .moveSpeed = 1.0f,
    .moveTime = 60,
    .waitTime = 60,
    .alertRadius = 90.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 4.5f,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 40.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_BuzzyBeetle) = {
    Call(SetSelfVar, AI_TACKLE_VAR_PRE_DELAY, 5)
    Call(SetSelfVar, AI_TACKLE_VAR_MIN_CHASE_TIME, 2)
    Call(SetSelfVar, AI_TACKLE_VAR_POST_DELAY, 5)
    Call(SetSelfVar, AI_TACKLE_VAR_TYPE, TACKLER_BUZZY_BEETLE)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_BuzzyBeetle)))
    Return
    End
};

MobileAISettings N(AISettings_SpikeTop) = {
    .moveSpeed = 1.0f,
    .moveTime = 60,
    .waitTime = 60,
    .alertRadius = 90.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 7.0f,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 40.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_SpikeTop) = {
    Call(SetSelfVar, AI_TACKLE_VAR_PRE_DELAY, 4)
    Call(SetSelfVar, AI_TACKLE_VAR_MIN_CHASE_TIME, 10)
    Call(SetSelfVar, AI_TACKLE_VAR_POST_DELAY, 4)
    Call(SetSelfVar, AI_TACKLE_VAR_TYPE, TACKLER_SPIKE_TOP)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_SpikeTop)))
    Return
    End
};

MobileAISettings N(AISettings_BonyBeetle) = {
    .moveSpeed = 1.0f,
    .moveTime = 20,
    .waitTime = 5,
    .alertRadius = 120.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 6.0f,
    .chaseRadius = 150.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_BonyBeetle) = {
    Call(SetSelfVar, AI_TACKLE_VAR_PRE_DELAY, 3)
    Call(SetSelfVar, AI_TACKLE_VAR_MIN_CHASE_TIME, 8)
    Call(SetSelfVar, AI_TACKLE_VAR_POST_DELAY, 6)
    Call(SetSelfVar, AI_TACKLE_VAR_TYPE, TACKLER_BONY_BEETLE)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_BonyBeetle)))
    Return
    End
};

#include "world/common/todo/AwaitPlayerNearNpc.inc.c"

EvtScript N(EVS_NpcAI_BuzzyBeetle_Ceiling) = {
    Call(N(func_80240814_97BE44))
    Call(SetNpcAnimation, NPC_SELF, ANIM_BuzzyBeetle_Anim0F)
    Call(N(AwaitPlayerNearNpc))
    Call(SelfEnemyOverrideSyncPos, 1)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, true)
    Call(SetNpcAnimation, NPC_SELF, ANIM_BuzzyBeetle_Anim00)
    Call(N(func_802408B4_97BEE4))
    Call(SelfEnemyOverrideSyncPos, 0)
    Call(SetSelfVar, AI_TACKLE_VAR_PRE_DELAY, 5)
    Call(SetSelfVar, AI_TACKLE_VAR_MIN_CHASE_TIME, 2)
    Call(SetSelfVar, AI_TACKLE_VAR_POST_DELAY, 5)
    Call(SetSelfVar, AI_TACKLE_VAR_TYPE, TACKLER_BUZZY_BEETLE)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_BuzzyBeetle)))
    Return
    End
};

NpcSettings N(NpcSettings_BuzzyBeetle) = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_BUZZY_BEETLE,
    .doAI = &N(EVS_NpcAI_BuzzyBeetle),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

NpcSettings N(NpcSettings_BuzzyBeetle_Ceiling) = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_BUZZY_BEETLE,
    .doAI = &N(EVS_NpcAI_BuzzyBeetle_Ceiling),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

NpcSettings N(NpcSettings_SpikeTop) = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_SPIKE_TOP,
    .doAI = &N(EVS_NpcAI_SpikeTop),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

NpcSettings N(NpcSettings_BonyBeetle) = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_BONY_BEETLE,
    .doAI = &N(EVS_NpcAI_BonyBeetle),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
