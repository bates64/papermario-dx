#include "tik_14.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList N(DripVolumes) = {
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

EvtScript N(EVS_SetupDrips) = {
    Set(LVar0, Ref(N(DripVolumes)))
    Set(LVar1, MODEL_sizuku)
    Exec(N(EVS_CreateDripVolumes))
    Return
    End
};
