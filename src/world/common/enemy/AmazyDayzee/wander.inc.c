#pragma once
#include "wander.h"

#include "world/common/ai/AvoidPlayerAI.inc.c"

MobileAISettings AISettings_AmazyDayzee_Wander = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 2.4f,
    .chaseTurnRate = 15,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 30.0f,
    .loiterMode = 1,
};

EvtScript EVS_NpcAI_AmazyDayzee_Wander = {
    Call(AvoidPlayerAI_Main, Ref(AISettings_AmazyDayzee_Wander))
    Return
    End
};

EvtScript EVS_NpcAux_AmazyDayzee_Wander = {
    Label(0)
        Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 30)
        Sub(LVar2, 2)
        PlayEffect(EFFECT_SPARKLES, 3, LVar0, LVar1, LVar2, 30)
        Wait(15)
        Goto(0)
    Return
    End
};

NpcSettings NpcSettings_AmazyDayzee_Wander = {
    .height = 30,
    .radius = 24,
    .level = ACTOR_LEVEL_AMAZY_DAYZEE,
    .doAux = &EVS_NpcAux_AmazyDayzee_Wander,
    .doAI = &EVS_NpcAI_AmazyDayzee_Wander,
    .onHit = &EnemyNpcHit,
    .onDefeat = &EnemyNpcDefeat,
};
