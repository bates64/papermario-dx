#pragma once
#include "idle.h"

#define EVAR_USE_COUNT 0
#define EVAR_IN_USE 1

API_CALLABLE(N(HeartPlant_SpawnHeart)) {
    Enemy* enemy = script->owner1.enemy;
    Npc* npc = get_npc_unsafe(enemy->npcID);

    if ((enemy->varTable[EVAR_USE_COUNT] < 5) && (rand_int(1000) > 300)) {
        make_item_entity_nodelay(ITEM_HEART, npc->pos.x, npc->pos.y + npc->collisionHeight, npc->pos.z + 5.0,
            ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS, 0);
        enemy->varTable[EVAR_USE_COUNT]++;
    }
    return ApiStatus_DONE2;
}

extern EvtScript N(EVS_NpcInteract_HeartPlant);

EvtScript N(EVS_NpcCreate_HeartPlant) = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetSelfVar, EVAR_USE_COUNT, 0)
    Call(SetSelfVar, EVAR_IN_USE, false)
    Return
    End
};

EvtScript N(EVS_HeartPlant_RebindInteractAfterDelay) = {
    Wait(45)
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_HeartPlant)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_HeartPlant) = {
    Call(GetSelfVar, EVAR_IN_USE, LVar0)
    IfEq(LVar0, false)
        Call(SetSelfVar, EVAR_IN_USE, true)
        Call(PlaySoundAtNpc, NPC_SELF, SOUND_HEART_PLANT, SOUND_SPACE_DEFAULT)
        Call(SetNpcAnimation, NPC_SELF, ANIM_HeartPlant_Idle)
        Wait(1)
        Call(N(HeartPlant_SpawnHeart))
        Call(SetNpcAnimation, NPC_SELF, ANIM_HeartPlant_Interact)
        Thread
            Call(BindNpcInteract, NPC_SELF, nullptr)
            Exec(N(EVS_HeartPlant_RebindInteractAfterDelay))
            Wait(45)
            Call(SetSelfVar, EVAR_IN_USE, false)
            Call(SetNpcAnimation, NPC_SELF, ANIM_HeartPlant_Idle)
        EndThread
    EndIf
    Return
    End
};

NpcSettings N(NpcSettings_HeartPlant) = {
    .height = 20,
    .radius = 28,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_HeartPlant),
    .onInteract = &N(EVS_NpcInteract_HeartPlant),
};
