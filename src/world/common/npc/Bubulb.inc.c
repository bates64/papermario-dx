#include "common.h"
#include "Bubulb.h"

EvtScript N(EVS_NpcCreate_Bubulb) = {
    Return
    End
};

NpcSettings N(NpcSettings_Bubulb) = {
    .height = 42,
    .radius = 26,
    .level = ACTOR_LEVEL_NONE,
    .onCreate = &N(EVS_NpcCreate_Bubulb),
};
