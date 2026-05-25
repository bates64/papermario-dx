#include "StarRod.h"

EvtScript N(EVS_NpcAuxAI_StarRod) = {
    Return
    End
};

NpcSettings N(NpcSettings_StarRod) = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .auxAI = &N(EVS_NpcAuxAI_StarRod),
};
