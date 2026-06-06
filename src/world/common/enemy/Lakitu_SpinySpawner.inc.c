#include "Lakitu.h"
#include "Spiny.h"

#include "world/common/enemy/ai/LakituAI.inc.c"

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

#include "world/common/enemy/ai/SpinyAI.inc.c"

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
