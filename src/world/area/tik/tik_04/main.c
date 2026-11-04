#include "tik_04.h"
#include "world/area/tik/tik_03.h"
#include "world/area/tik/tik_05.h"
#include "world/area/tik/tik_07.h"
#include "world/area/tik/tik_12.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_05_0 = EVT_EXIT_WALK(60, $SpringRoom, $tik_05.ScalesRoom);
EvtScript EVS_ExitWalk_tik_07_0 = EVT_EXIT_WALK(60, $ElevatorAtticRoom, $tik_07.ScalesRoom);

EvtScript EVS_GotoMap_tik_03_1 = {
    Call(GotoMap, $tik_03.ScalesRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_03_1 = EVT_EXIT_PIPE_HORIZONTAL($ShortElevatorRoom, COLLIDER_ttd, EVS_GotoMap_tik_03_1);

EvtScript EVS_GotoMap_tik_12_0 = {
    Call(GotoMap, $tik_12.ScalesRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_12_0 = EVT_EXIT_PIPE_VERTICAL($MetalBlockRoom, COLLIDER_ttd2, EVS_GotoMap_tik_12_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_tik_07_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitPipe_tik_03_1, TRIGGER_WALL_PUSH, COLLIDER_ttd, 1, 0)
    BindTrigger(EVS_ExitPipe_tik_12_0, TRIGGER_FLOOR_TOUCH, COLLIDER_ttd2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupDrips)
    // water leaking
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Exec(EVS_SetupPlatforms)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ShortElevatorRoom.index)
            EVT_ENTER_PIPE_HORIZONTAL(COLLIDER_ttd, EVS_BindExitTriggers)
        CaseEq($MetalBlockRoom.index)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Return
    End
};
