#include "tik_07.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 3,
    .volumes = {
        {
            .minPos = { $DripVolume_1.min.x, $DripVolume_1.min.z },
            .maxPos = { $DripVolume_1.max.x, $DripVolume_1.max.z },
            .startY = $DripVolume_1.max.y,
            .endY = $DripVolume_1.min.y,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = { $DripVolume_2.min.x, $DripVolume_2.min.z },
            .maxPos = { $DripVolume_2.max.x, $DripVolume_2.max.z },
            .startY = $DripVolume_2.max.y,
            .endY = $DripVolume_2.min.y,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = { $DripVolume_3.min.x, $DripVolume_3.min.z },
            .maxPos = { $DripVolume_3.max.x, $DripVolume_3.max.z },
            .startY = $DripVolume_3.max.y,
            .endY = $DripVolume_3.min.y,
            .duration = 40,
            .density  = 1,
        },
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, DripVolumes)
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};
