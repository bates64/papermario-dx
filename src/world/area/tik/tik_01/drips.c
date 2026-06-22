#include "tik_01.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList N(DripVolumes) = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -175,  -65 },
            .maxPos = {  485,  140 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 4,
        }
    }
};

EvtScript N(EVS_SetupDrips) = {
    Set(LVar0, Ref(N(DripVolumes)))
    Set(LVar1, MODEL_sizuku)
    Exec(N(EVS_CreateDripVolumes))
    Return
    End
};
