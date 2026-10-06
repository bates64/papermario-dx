#include "tik_08.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
    .volumes = {
        {
            .minPos = { -519,  -19 },
            .maxPos = {  259,   46 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = {  133, -100 },
            .maxPos = {   45,  235 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 1,
        },
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, Ref(DripVolumes))
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};
