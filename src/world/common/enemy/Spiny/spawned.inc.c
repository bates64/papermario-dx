#pragma once
#include "spawned.h"

#include "world/common/ai/SpinyAI.inc.c"

MobileAISettings N(AISettings_SpawnedSpiny) = {
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

EvtScript N(EVS_NpcAI_SpawnedSpiny) = {
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 3)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 18)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 3)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_SPINY)
    Call(N(SpinyAI_Main), Ref(N(AISettings_SpawnedSpiny)))
    Return
    End
};

EvtScript N(EVS_NpcDefeat_SpawnedSpiny) = {
    Call(SetNpcRotation, NPC_SELF, 0, 0, 0)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(SetSelfVar, AI_VAR_SPINY_STATUS, SPINY_STATUS_RESET)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(OnPlayerFled, false)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

NpcSettings N(NpcSettings_SpawnedSpiny) = {
    .height = 21,
    .radius = 22,
    .level = ACTOR_LEVEL_SPINY,
    .doAI = &N(EVS_NpcAI_SpawnedSpiny),
    .onHit = &EnemyNpcHit,
    .onDefeat = &N(EVS_NpcDefeat_SpawnedSpiny),
};
