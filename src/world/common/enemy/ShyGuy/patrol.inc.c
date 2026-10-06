#pragma once
#include "patrol.h"

#include "world/common/ai/ShyGuyPatrolAI.inc.c"

MobileAISettings AISettings_ShyGuy_Patrol = {
    .moveSpeed = 2.0f,
    .moveTime = 60,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 6,
    .chaseUpdateInterval = 1,
    .chaseRadius = 160.0f,
    .chaseOffsetDist = 50.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_ShyGuy_Patrol = {
    Call(ShyGuyPatrolAI_Main, Ref(AISettings_ShyGuy_Patrol))
    Return
    End
};

EvtScript EVS_NpcAI_ShyGuy_Patrol_Passive = {
    Call(PatrolNoAttackAI_Main, Ref(AISettings_ShyGuy_Patrol))
    Return
    End
};

NpcSettings NpcSettings_ShyGuy_Patrol = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_SHY_GUY,
    .doAI = &EVS_NpcAI_ShyGuy_Patrol,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};

NpcSettings NpcSettings_ShyGuy_Patrol_Passive = {
    .height = 23,
    .radius = 22,
    .level = ACTOR_LEVEL_SHY_GUY,
    .doAI = &EVS_NpcAI_ShyGuy_Patrol_Passive,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
    .actionFlags = AI_ACTION_JUMP_WHEN_SEE_PLAYER,
};
