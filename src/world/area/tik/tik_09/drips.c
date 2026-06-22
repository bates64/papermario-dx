#include "tik_09.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList N(DripVolumes) = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -223,  -31 },
            .maxPos = {  550,   68 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 3,
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
