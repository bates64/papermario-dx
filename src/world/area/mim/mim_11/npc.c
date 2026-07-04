#include "mim_11.h"
#include "world/common/npc/Bootler/base.h"

#include "world/common/npc/Boo/idle.inc.c"
#include "world/common/npc/StarSpirit/idle.inc.c"

API_CALLABLE(N(AnimateStarSpiritBobbing)) {
    Npc* npc;

    if (isInitialCall) {
        script->functionTemp[1] = 0;
        script->functionTempPtr[2] = get_npc_safe(script->owner2.npcID);
    }

    npc = script->functionTempPtr[2];
    npc->verticalRenderOffset = sin_deg(script->functionTempF[1]) * 6.0f;
    script->functionTempF[1] = clamp_angle(script->functionTempF[1] + 18.0f);
    return ApiStatus_BLOCK;
}

EvtScript N(EVS_NpcAux_Skolar) = {
    Call(N(AnimateStarSpiritBobbing))
    Return
    End
};

EvtScript N(EVS_NpcInit_Skolar) = {
    Call(BindNpcAux, NPC_SELF, Ref(N(EVS_NpcAux_Skolar)))
    Call(SetNpcPos, NPC_SELF, 0, -1000, -100)
    Call(EnableNpcShadow, NPC_SELF, false)
    IfNe(GB_StoryProgress, STORY_CH3_DEFEATED_TUBBA_BLUBBA)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_Bootler) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_OPENED_BOOS_MANSION_GATE)
            Call(EnableNpcShadow, NPC_SELF, false)
            Call(SetNpcImgFXParams, NPC_SELF, IMGFX_SET_ALPHA, 0, 0, 0, 0)
        CaseDefault
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

NpcData N(NpcData_Bootler)[] = {
    {
        .id = NPC_Bootler,
        .pos = { 68.0f, 60.0f, -145.0f },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Bootler),
        .settings = &N(NpcSettings_Boo),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BOOTLER_ANIMS,
    },
    {
        .id = NPC_Skolar,
        .pos = { 68.0f, 60.0f, -145.0f },
        .yaw = 135,
        .init = &N(EVS_NpcInit_Skolar),
        .settings = &N(NpcSettings_StarSpirit),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = SKOLAR_ANIMS,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Bootler)),
    {}
};
