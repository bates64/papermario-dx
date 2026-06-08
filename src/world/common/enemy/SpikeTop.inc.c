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
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 5)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 2)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 5)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_BUZZY_BEETLE)
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
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 4)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 10)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 4)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_SPIKE_TOP)
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
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 3)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 8)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 6)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_BONY_BEETLE)
    Call(N(TackleWanderAI_Main), Ref(N(AISettings_BonyBeetle)))
    Return
    End
};

API_CALLABLE(N(BuzzyBeetle_OffsetHeight)) {
    Npc* npc = get_npc_safe(script->owner2.npcID);

    npc->verticalRenderOffset = npc->collisionHeight;
    npc->pos.y -= (f32) npc->collisionHeight;

    return ApiStatus_DONE2;
}

API_CALLABLE(N(BuzzyBeetle_AwaitPlayerNear)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = get_npc_safe(script->owner2.npcID);

    if (dist2D(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z) < 50.0f) {
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(N(BuzzyBeetle_AwaitLanding)) {
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_safe(script->owner2.npcID);

    if (isInitialCall) {
        npc->verticalRenderOffset = 0;
    }

    if (npc->flags & NPC_FLAG_GROUNDED) {
        currentEncounter->encounterList[enemy->encounterIndex]->battle = enemy->varTable[0];
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

EvtScript N(EVS_NpcAI_BuzzyBeetle_Ceiling) = {
    Call(N(BuzzyBeetle_OffsetHeight))
    Call(SetNpcAnimation, NPC_SELF, ANIM_BuzzyBeetle_Anim0F)
    Call(N(BuzzyBeetle_AwaitPlayerNear))
    Call(EnemyEnableFirstStrike, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY, true)
    Call(SetNpcAnimation, NPC_SELF, ANIM_BuzzyBeetle_Anim00)
    Call(N(BuzzyBeetle_AwaitLanding))
    Call(EnemyEnableFirstStrike, false)
    Call(SetSelfVar, AI_VAR_TACKLE_PRE_DELAY, 5)
    Call(SetSelfVar, AI_VAR_TACKLE_MIN_CHASE_TIME, 2)
    Call(SetSelfVar, AI_VAR_TACKLE_POST_DELAY, 5)
    Call(SetSelfVar, AI_VAR_TACKLE_TYPE, TACKLER_BUZZY_BEETLE)
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
