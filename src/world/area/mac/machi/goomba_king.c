#include "machi.h"

EvtScript EVS_GoombaKing_Init = {
    Return
    End
};

EvtScript EVS_NpcCreate_GoombaKing = {
    Call(SetNpcScale, NPC_SELF, Float(0.5), Float(0.5), Float(0.5))
    Return
    End
};

EvtScript EVS_NpcInteract_GoombaKing = {
    Return
    End
};

EvtScript EVS_NpcAI_GoombaKing = {
    Return
    End
};

EvtScript EVS_NpcHit_GoombaKing = {
    Return
    End
};

EvtScript EVS_NpcDefeat_GoombaKing = {
    Return
    End
};

NpcSettings NpcSettings_GoombaKing = {
    .defaultAnim = ANIM_GoombaKing_Idle,
    .height = 24,
    .radius = 24,
    .doAI = &EVS_NpcAI_GoombaKing,
    .onCreate = &EVS_NpcCreate_GoombaKing,
    .onInteract = &EVS_NpcInteract_GoombaKing,
    .onHit = &EVS_NpcHit_GoombaKing,
    .flags = BASE_PASSIVE_FLAGS,
};
