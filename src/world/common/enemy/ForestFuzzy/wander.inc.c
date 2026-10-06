#pragma once
#include "wander.h"

#include "world/common/ai/HoppingAI.inc.c"

MobileAISettings AISettings_ForestFuzzy_Wander = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 10,
    .alertRadius = 120.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 5,
    .chaseRadius = 160.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_ForestFuzzy_Wander = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, true)
    Call(SetSelfVar, AI_VAR_HOPPER, HOPPER_FOREST_FUZZY)
    Call(HoppingAI_Main, Ref(AISettings_ForestFuzzy_Wander))
    Return
    End
};

NpcSettings NpcSettings_ForestFuzzy_Wander = {
    .height = 20,
    .radius = 22,
    .level = ACTOR_LEVEL_FOREST_FUZZY,
    .doAI = &EVS_NpcAI_ForestFuzzy_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
