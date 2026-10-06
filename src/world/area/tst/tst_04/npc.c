#include "tst_04.h"

API_CALLABLE(DisableOwnerShadow) {
    disable_npc_shadow(get_npc_unsafe(script->owner1.enemy->npcID));
    return ApiStatus_DONE2;
}

EvtScript EVS_NpcCreate_Goompa = {
    Call(DisableOwnerShadow)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CAMERA_FOR_YAW, true)
    Return
    End
};

EvtScript EVS_NpcAux_Goompa = {
    Return
    End
};

EvtScript EVS_NpcAI_Goompa = {
    Return
    End
};

EvtScript EVS_NpcHit_Goompa = {
    Return
    End
};

EvtScript EVS_NpcInteract_Goompa = {
    Return
    End
};

EvtScript EVS_NpcDefeat_Goompa = {
    Return
    End
};

NpcSettings NpcSettings_Goompa = {
    .defaultAnim = ANIM_Goompa_Talk,
    .height = 24,
    .radius = 24,
    .doAux = &EVS_NpcAux_Goompa,
    .doAI = &EVS_NpcAI_Goompa,
    .onCreate = &EVS_NpcCreate_Goompa,
    .onInteract = &EVS_NpcInteract_Goompa,
    .onHit = &EVS_NpcHit_Goompa,
    .onDefeat = &EVS_NpcDefeat_Goompa,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL,
};

NpcData NpcData_GoombaFamily = {
    .id = NPC_Goompa,
    .pos = { 80.0f, 40.0f, -84.0f },
    .yaw = 0,
    .settings = &NpcSettings_Goompa,
    .flags = ENEMY_FLAG_GRAVITY,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_GoombaFamily),
    {}
};
