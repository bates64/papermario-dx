#include "tik_06.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
    .volumes = {
        {
            .minPos = { -512,  -14 },
            .maxPos = {  173,   84 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = {   63, -105 },
            .maxPos = {  103,  182 },
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
