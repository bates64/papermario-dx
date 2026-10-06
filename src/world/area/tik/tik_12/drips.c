#include "tik_12.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
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

EvtScript EVS_SetupDrips = {
    Set(LVar0, Ref(DripVolumes))
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};
