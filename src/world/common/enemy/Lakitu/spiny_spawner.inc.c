#pragma once
#include "spiny_spawner.h"

#include "world/common/ai/LakituAI.inc.c"

MobileAISettings N(AISettings_Lakitu_SpinySpawner) = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 60.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 10,
    .chaseRadius = 80.0f,
    .chaseOffsetDist = 70.0f,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_Lakitu_SpinySpawner) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(-6.5))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.3))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(4.0))
    Call(N(LakituAI_Main), Ref(N(AISettings_Lakitu_SpinySpawner)))
    Return
    End
};

NpcSettings N(NpcSettings_Lakitu_SpinySpawner) = {
    .height = 28,
    .radius = 24,
    .level = ACTOR_LEVEL_LAKITU,
    .doAI = &N(EVS_NpcAI_Lakitu_SpinySpawner),
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};

#include "world/common/enemy/Spiny/spawned.inc.c"
