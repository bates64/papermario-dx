#include "jan_11.h"
#include "world/area/jan/jan_09.h"

#include "world/common/util/CreateDarkness.inc.c"

#include "world/common/entity/Pipe.inc.c"

#include "world/area/tik/common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
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
        }
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, DripVolumes)
    Set(LVar1, MODEL_o140)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};

EvtScript EVS_GotoMap_jan_09_3 = {
    Call(GotoMap, $jan_09.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_jan_09_3 = EVT_EXIT_PIPE_HORIZONTAL($Jan09, COLLIDER_o10, EVS_GotoMap_jan_09_3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitPipe_jan_09_3, TRIGGER_WALL_PUSH, COLLIDER_o10, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_CreateDarkness)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupDrips)
    Return
    End
};
