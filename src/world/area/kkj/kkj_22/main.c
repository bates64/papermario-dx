#include "kkj_22.h"
#include "world/area/kkj/kkj_13.h"
#include "world/area/kkj/kkj_23.h"

EvtScript EVS_ExitDoor_kkj_13_1 =
    EVT_EXIT_DOUBLE_DOOR($WindowHallway, $kkj_13.DoubleStaircase, COLLIDER_ttw, MODEL_o51, MODEL_o52);
EvtScript EVS_ExitDoor_kkj_23_0 =
    EVT_EXIT_DOUBLE_DOOR($Rooftop, $kkj_23.DoubleStaircase, COLLIDER_ttnw, MODEL_o94, MODEL_o95);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($WindowHallway.index)
            Set(LVar2, MODEL_o51)
            Set(LVar3, MODEL_o52)
            ExecWait(EnterDoubleDoor)
        CaseEq($Rooftop.index)
            Set(LVar2, MODEL_o94)
            Set(LVar3, MODEL_o95)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    BindTrigger(EVS_ExitDoor_kkj_13_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoor_kkj_23_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttnw, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
