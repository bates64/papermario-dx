#include "tik_02.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
    .volumes = {
        {
            .minPos = { -374,  -98 },
            .maxPos = {  102,  158 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = {   66, -106 },
            .maxPos = {  182,  152 },
            .startY = 200,
            .endY   = -10,
            .duration = 60,
            .density  = 2,
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
