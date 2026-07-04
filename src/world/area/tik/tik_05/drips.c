#include "tik_05.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList N(DripVolumes) = {
    .count = 1,
    .volumes = {
        {
            .minPos = {  -21,  -90 },
            .maxPos = {   86,  156 },
            .startY = 300,
            .endY   = -10,
            .duration = 90,
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
