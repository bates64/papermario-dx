#pragma once
#include "wander.h"

#include "world/common/ai/HoppingAI.inc.c"

MobileAISettings AISettings_JungleFuzzy_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 10,
    .alertRadius = 150.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 5.0f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 5,
    .chaseRadius = 200.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_JungleFuzzy_Wander = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, true)
    Call(SetSelfVar, AI_VAR_HOPPER, HOPPER_JUNGLE_FUZZY)
    Call(HoppingAI_Main, Ref(AISettings_JungleFuzzy_Wander))
    Return
    End
};

NpcSettings NpcSettings_JungleFuzzy_Wander = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_JUNGLE_FUZZY,
    .doAI = &EVS_NpcAI_JungleFuzzy_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
