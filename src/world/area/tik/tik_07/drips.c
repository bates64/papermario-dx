#include "tik_07.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 3,
    .volumes = {
        {
            .minPos = { -264,  -61 },
            .maxPos = {  150,  188 },
            .startY = 230,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = {   31,  -20 },
            .maxPos = {  297,  156 },
            .startY = 230,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = {  108, -117 },
            .maxPos = {   56,   43 },
            .startY = 230,
            .endY   = 90,
            .duration = 40,
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
