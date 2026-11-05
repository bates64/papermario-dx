#include "tik_23.h"
#include "world/area/tik/tik_20.h"
#include "world/area/tik/tik_24.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_24_1 = EVT_EXIT_WALK(60, $HallToUltraBoots, $tik_24.WindyPath);

EvtScript EVS_GotoMap_tik_20_2 = {
    Call(GotoMap, $tik_20.WindyPath)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_20_2 = EVT_EXIT_PIPE_HORIZONTAL($SpikesRoom, COLLIDER_ttd, EVS_GotoMap_tik_20_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_24_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitPipe_tik_20_2, TRIGGER_WALL_PUSH, COLLIDER_ttd, 1, 0)
    Return
    End
};

#include "../common/DripVolumes.inc.c"

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
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};

#include "../common/Flotsam.inc.c"

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $SpikesRoom.index)
        EVT_ENTER_PIPE_HORIZONTAL(COLLIDER_ttd, EVS_BindExitTriggers)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    Wait(1)
    Exec(EVS_SetupMusic)
    Call(PlaySound, SOUND_LOOP_TIK23_WATER)
    ExecWait(EVS_SetupDrips)
    Call(SetTexPanner, MODEL_nagare1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o97, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o98, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o99, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(   70, -100,  100, -130)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar2, MODEL_bin)
        Exec(EVS_Flotsam_Bobbing)
        Wait(5)
        Set(LVar2, MODEL_kan1)
        Exec(EVS_Flotsam_Bobbing)
        Wait(5)
        Set(LVar2, MODEL_kan2)
        Exec(EVS_Flotsam_Bobbing)
    EndThread
    Return
    End
};
