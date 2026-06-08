#include "StarRod.h"

EvtScript N(EVS_NpcCreate_StarRod) = {
    Return
    End
};

NpcSettings N(NpcSettings_StarRod) = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_StarRod),
};
