#pragma once
#include "wander.h"

API_CALLABLE(SetPokeyInstigatorValue) {
    script->owner1.enemy->instigatorValue = 3;
    return ApiStatus_DONE2;
}

MobileAISettings AISettings_Pokey_Wander = {
    .moveSpeed = 1.8f,
    .moveTime = 50,
    .waitTime = 10,
    .alertRadius = 250.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 45,
    .chaseUpdateInterval = 6,
    .chaseRadius = 300.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_Pokey_Wander = {
    Call(SetPokeyInstigatorValue)
    Call(BasicAI_Main, Ref(AISettings_Pokey_Wander))
    Return
    End
};

NpcSettings NpcSettings_Pokey_Wander = {
    .height = 72,
    .radius = 15,
    .level = ACTOR_LEVEL_POKEY,
    .doAI = &EVS_NpcAI_Pokey_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
