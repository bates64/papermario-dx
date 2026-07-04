#include "tik_12.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList N(DripVolumes) = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -216,  -56 },
            .maxPos = {  318,  193 },
            .startY = 200,
            .endY   = -135,
            .duration = 100,
            .density  = 3,
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
