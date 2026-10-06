#include "tik_22.h"

#include "world/common/entity/Pipe.inc.c"

API_CALLABLE(ResetTrackVolumes) {
    bgm_clear_track_volumes(0, TRACK_VOLS_TIK_SHIVER);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitDoors_tik_21_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(ResetTrackVolumes)
    Set(LVar0, tik_22_ENTRY_0)
    Set(LVar1, COLLIDER_tte)
    Set(LVar2, MODEL_o46)
    Set(LVar3, MODEL_o47)
    Exec(ExitDoubleDoor)
    Wait(17)
    Call(GotoMap, Ref("tik_21"), tik_21_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_tik_17_0 = {
    Call(GotoMap, Ref("tik_17"), tik_17_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_17_0 = EVT_EXIT_PIPE_VERTICAL(tik_22_ENTRY_1, COLLIDER_o61, EVS_GotoMap_tik_17_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_tik_21_1), TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(Ref(EVS_ExitPipe_tik_17_0), TRIGGER_FLOOR_TOUCH, COLLIDER_o61, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(tik_22_ENTRY_0)
            Set(LVar2, MODEL_o46)
            Set(LVar3, MODEL_o47)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(tik_22_ENTRY_1)
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
            .minPos = { -220,  -19 },
            .maxPos = {   60,   46 },
            .startY = 200,
            .endY   = 0,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = {   63, -100 },
            .maxPos = {   47,  235 },
            .startY = 200,
            .endY   = 0,
            .duration = 60,
            .density  = 1,
        }
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, Ref(DripVolumes))
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    Call(SetSpriteShading, SHADING_TIK_22)
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
