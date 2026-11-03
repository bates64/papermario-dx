#include "kkj_02.h"
#include "world/area/kkj/kkj_01.h"
#include "world/area/kkj/kkj_03.h"

EvtScript EVS_ExitDoors_kkj_01_1 =
    EVT_EXIT_DOUBLE_DOOR($UpperHall, $kkj_01.StairsHallway, COLLIDER_deilit1, MODEL_door1, MODEL_door2);
EvtScript EVS_ExitDoors_kkj_03_0 =
    EVT_EXIT_DOUBLE_DOOR($WindowHallway, $kkj_03.StairsHallway, COLLIDER_deilit2, MODEL_door4, MODEL_door3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kkj_01_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilit1, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_03_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilit2, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($UpperHall.index)
            Set(LVar2, MODEL_door1)
            Set(LVar3, MODEL_door2)
            ExecWait(EnterDoubleDoor)
        CaseEq($WindowHallway.index)
            Set(LVar2, MODEL_door4)
            Set(LVar3, MODEL_door3)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACH_CASTLE_GROUNDS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    Exec(EVS_BindExitTriggers)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
