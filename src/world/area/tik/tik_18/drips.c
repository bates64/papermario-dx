#include "tik_18.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -233, -117 },
            .maxPos = {  545,  187 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 4,
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
