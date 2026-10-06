#include "tik_15.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -220,  -18 },
            .maxPos = {  243,  155 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
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
