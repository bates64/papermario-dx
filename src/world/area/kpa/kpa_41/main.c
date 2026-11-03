#include "kpa_41.h"
#include "world/area/kpa/kpa_102.h"
#include "world/area/kpa/kpa_40.h"

EvtScript EVS_ExitWalk_LowerLeft = EVT_EXIT_WALK(60, $LowerLeft, $kpa_40.LowerRight);

EvtScript EVS_ExitWalk_LowerRight = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $LowerRight.index)
    Exec(ExitWalk)
    Switch(AB_KPA_MazeProgress)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Add(AB_KPA_MazeProgress, 1)
            Call(GotoMap, $LowerLeft)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(3)
        CaseOrEq(5)
            Call(GotoMap, $kpa_40.UpperLeft)
        EndCaseGroup
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_UpperLeft = EVT_EXIT_WALK(60, $UpperLeft, $kpa_40.UpperRight);

EvtScript EVS_ExitWalk_UpperRight = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $UpperRight.index)
    Exec(ExitWalk)
    Switch(AB_KPA_MazeProgress)
        CaseEq(5)
            Set(AB_KPA_MazeProgress, 0)
            Call(GotoMap, $kpa_102.MazeRoom)
        CaseEq(3)
            Add(AB_KPA_MazeProgress, 1)
            Call(GotoMap, $UpperLeft)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Call(GotoMap, $kpa_40.UpperLeft)
        EndCaseGroup
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_LowerLeft, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_LowerRight, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_UpperLeft, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    BindTrigger(EVS_ExitWalk_UpperRight, TRIGGER_FLOOR_ABOVE, COLLIDER_deili4, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($UpperRight.index)
            Set(AB_KPA_MazeProgress, 5)
        CaseDefault
    EndSwitch
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(EVS_EnterMap)
    Exec(EVS_SetupMusic)
    Return
    End
};
