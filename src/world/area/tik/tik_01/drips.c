#include "tik_01.h"

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 1,
    .volumes = {
        {
            .minPos = { $DripVolume_1.min.x, $DripVolume_1.min.z },
            .maxPos = { $DripVolume_1.max.x, $DripVolume_1.max.z },
            .startY = $DripVolume_1.max.y,
            .endY = $DripVolume_1.min.y,
            .duration = 60,
            .density  = 4,
        }
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, DripVolumes)
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};
