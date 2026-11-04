#include "tik_20.h"
#include "world/area/tik/tik_08.h"
#include "world/area/tik/tik_21.h"
#include "world/area/tik/tik_23.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_08_1 = EVT_EXIT_WALK(60, $SecondLevelEntry, $tik_08.SpikesRoom);
EvtScript EVS_ExitWalk_tik_21_0 = EVT_EXIT_WALK(60, $HiddenBlocksRoom, $tik_21.SpikesRoom);

EvtScript EVS_GotoMap_tik_23_1 = {
    Call(GotoMap, $tik_23.SpikesRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_23_1 = EVT_EXIT_PIPE_VERTICAL($WindyPath, COLLIDER_o109, EVS_GotoMap_tik_23_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_08_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_tik_21_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitPipe_tik_23_1, TRIGGER_FLOOR_TOUCH, COLLIDER_o109, 1, 0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_yuka, .pos = $LavaReset_yuka.pos },
    { .colliderID = COLLIDER_yuka2, .pos = $LavaReset_yuka2.pos },
    { .colliderID = NO_COLLIDER }
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
            .density  = 1,
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
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_toge, SURFACE_TYPE_SPIKES)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    Exec(EVS_SetupMusic)
    Call(PlaySound, SOUND_LOOP_TIK20_WATER)
    Exec(EVS_SetupDrips)
    Call(SetTexPanner, MODEL_nagare, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(   70,  100,  100,  130)
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
    Wait(1)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq($SecondLevelEntry.index)
        CaseOrEq($HiddenBlocksRoom.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        EndCaseGroup
        CaseEq($WindyPath.index)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
    EndSwitch
    Wait(1)
    Return
    End
};
