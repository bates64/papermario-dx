#include "idle.h"

EvtScript N(EVS_NpcInit_Merlee) = {
    Return
    End
};

NpcSettings N(NpcSettings_Merlee) = {
    .height = 32,
    .radius = 32,
    .onInteract = &N(EVS_NpcInteract_Merlee),
    .level = ACTOR_LEVEL_NONE,
};
