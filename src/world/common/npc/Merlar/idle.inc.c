#pragma once
#include "idle.h"

API_CALLABLE(N(AddMerlarHoverMotion_Idle)) {
    Npc* npc;

    if (isInitialCall) {
        script->functionTempF[1] = 0.0f;
        script->functionTempPtr[2] = get_npc_safe(script->owner2.npcID);
    }
    npc = script->functionTempPtr[2];
    npc->verticalRenderOffset = sin_deg(script->functionTempF[1]) * 5.0f;
    script->functionTempF[1] = clamp_angle(script->functionTempF[1] + 4.5f);
    return ApiStatus_BLOCK;
}

EvtScript N(EVS_NpcCreate_Merlar_Idle) = {
    Return
    End
};

NpcSettings N(NpcSettings_Merlar) = {
    .height = 60,
    .radius = 60,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_Merlar_Idle),
};

EvtScript N(EVS_NpcAux_Merlar_Idle) = {
    Return
    End
};

EvtScript N(EVS_NpcIdle_Merlar_Idle) = {
    Call(N(AddMerlarHoverMotion_Idle))
    Return
    End
};
