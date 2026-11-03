#include "tik_22.h"
#include "world/area/tik/tik_17.h"
#include "world/area/tik/tik_21.h"

#include "world/common/entity/Pipe.inc.c"

API_CALLABLE(ResetTrackVolumes) {
    bgm_clear_track_volumes(0, TRACK_VOLS_TIK_SHIVER);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitDoors_tik_21_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(ResetTrackVolumes)
    Set(LVar0, $HiddenBlocksRoom.index)
    Set(LVar1, COLLIDER_tte)
    Set(LVar2, MODEL_o46)
    Set(LVar3, MODEL_o47)
    Exec(ExitDoubleDoor)
    Wait(17)
    Call(GotoMap, $tik_21.PathToShiverCity)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_tik_17_0 = {
    Call(GotoMap, $tik_17.PathToShiverCity)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_17_0 = EVT_EXIT_PIPE_VERTICAL($FrozenRoom, COLLIDER_o61, EVS_GotoMap_tik_17_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_tik_21_1, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ExitPipe_tik_17_0, TRIGGER_FLOOR_TOUCH, COLLIDER_o61, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($HiddenBlocksRoom.index)
            Set(LVar2, MODEL_o46)
            Set(LVar3, MODEL_o47)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($FrozenRoom.index)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
    EndSwitch
    Wait(1)
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

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    Call(SetSpriteShading, $SpriteShading)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Exec(EVS_SetupDrips)
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    0,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Wait(1)
    Exec(EVS_EnterMap)
    Return
    End
};
