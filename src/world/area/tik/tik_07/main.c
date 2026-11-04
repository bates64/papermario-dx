#include "tik_07.h"
#include "world/area/tik/tik_04.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_04_1 = EVT_EXIT_WALK(60, $ScalesRoom, $tik_04.ElevatorAtticRoom);

EvtScript EVS_GotoMap_tik_07_2 = {
    Call(GotoMap, $EastPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_tik_07_1 = {
    Call(GotoMap, $WestPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_tik_07_2 = EVT_EXIT_PIPE_VERTICAL($WestPipe, COLLIDER_dokan_e1, EVS_GotoMap_tik_07_2);
EvtScript EVS_ExitWalk_tik_07_1 = EVT_EXIT_PIPE_VERTICAL($EastPipe, COLLIDER_dokan_e2, EVS_GotoMap_tik_07_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_04_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_tik_07_2, TRIGGER_FLOOR_TOUCH, COLLIDER_dokan_e1, 1, 0)
    BindTrigger(EVS_ExitWalk_tik_07_1, TRIGGER_FLOOR_TOUCH, COLLIDER_dokan_e2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupDrips)
    Exec(EVS_SetupPlatforms)
    Wait(1)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $ScalesRoom.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
        EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
    EndIf
    Wait(1)
    Return
    End
};
