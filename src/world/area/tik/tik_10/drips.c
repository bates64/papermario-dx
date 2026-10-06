#include "tik_10.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
    .volumes = {
        {
            .minPos = { -220,   20 },
            .maxPos = {  110,   50 },
            .startY = 250,
            .endY   = 20,
            .duration = 60,
            .density  = 3,
        },
        {
            .minPos = {  160,   10 },
            .maxPos = {  160,   60 },
            .startY = 250,
            .endY   = 20,
            .duration = 60,
            .density  = 1,
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
