#include "jan_11.h"

#include "world/common/util/CreateDarkness.inc.c"

#include "world/common/entity/Pipe.inc.c"

#include "world/area/tik/common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
    .volumes = {
        {
            .minPos = { -154,  100 },
            .maxPos = {   92,   36 },
            .startY = 200,
            .endY   = 0,
            .duration = 60,
            .density  = 2,
        },
         {
            .minPos = {  212,   10 },
            .maxPos = {   53,  122 },
            .startY = 200,
            .endY   = 0,
            .duration = 60,
            .density  = 2,
        }
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, Ref(DripVolumes))
    Set(LVar1, MODEL_o140)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};

EvtScript EVS_GotoMap_jan_09_3 = {
    Call(GotoMap, Ref("jan_09"), jan_09_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_jan_09_3 = EVT_EXIT_PIPE_HORIZONTAL(jan_11_ENTRY_0, COLLIDER_o10, EVS_GotoMap_jan_09_3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitPipe_jan_09_3), TRIGGER_WALL_PUSH, COLLIDER_o10, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    Exec(EVS_CreateDarkness)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupDrips)
    Return
    End
};
