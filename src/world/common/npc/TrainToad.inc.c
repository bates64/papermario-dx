#include "TrainToad.h"

EvtScript N(EVS_NpcAuxAI_TrainToad) = {
    Return
    End
};

NpcSettings N(NpcSettings_TrainToad) = {
    .height = 32,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .auxAI = &N(EVS_NpcAuxAI_TrainToad),
};
