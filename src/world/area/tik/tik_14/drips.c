#include "tik_14.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -215,   35 },
            .maxPos = {  228,  102 },
            .startY = 210,
            .endY   = 0,
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
