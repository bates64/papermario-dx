#include "TrainToad.h"

EvtScript N(EVS_NpcCreate_TrainToad) = {
    Return
    End
};

NpcSettings N(NpcSettings_TrainToad) = {
    .height = 32,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_TrainToad),
};
