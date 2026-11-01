
#include "kpa_40.h"
#include "world/area/kpa/kpa_41.h"
#include "world/area/kpa/kpa_52.h"

EvtScript EVS_ExitDoors_kpa_52_1 =
    EVT_EXIT_DOUBLE_DOOR($SplitLevelHall, $kpa_52.MazeGuideRoom, COLLIDER_ttw, MODEL_o526, MODEL_o525);
EvtScript EVS_ExitWalk_kpa_40_3 = EVT_EXIT_WALK(60, $LowerRight, $UpperLeft);

EvtScript EVS_ExitWalk_kpa_41_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $UpperRight.index)
    Exec(ExitWalk)
    Set(AB_KPA_MazeProgress, 1)
    Call(GotoMap, $kpa_41.UpperLeft)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_52_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_40_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie2, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_41_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($SplitLevelHall.index)
            Set(LVar0, $SplitLevelHall.index)
            Set(LVar2, MODEL_o526)
            Set(LVar3, MODEL_o525)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
