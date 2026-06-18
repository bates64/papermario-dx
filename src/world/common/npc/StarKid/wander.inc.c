#pragma once
#include "wander.h"

#include "world/common/ai/FlyingAI.inc.c"

MobileAISettings N(AISettings_StarKid_Wander) = {
    .moveSpeed = 1.2f,
    .moveTime = 60,
    .waitTime = 30,
    .playerSearchInterval = -1,
    .loiterMode = 1,
};

EvtScript N(EVS_NpcAI_StarKid_Wander) = {
    Call(SetSelfVar, AI_VAR_FLYING_FLAGS, 0)
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_VELY, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_CHASE_ACCEL, AI_PACK_FLT(0.0f))
    Call(SetSelfVar, AI_VAR_FLYING_BOB_AMPLITUDE, AI_PACK_FLT(2.0f))
    Call(N(FlyingAI_Main), Ref(N(AISettings_StarKid_Wander)))
    Return
    End
};

NpcSettings N(NpcSettings_StarKid_Wander) = {
    .height = 20,
    .radius = 20,
    .level = ACTOR_LEVEL_NONE,
    .doAI = &N(EVS_NpcAI_StarKid_Wander),
};
