#include "kpa_08.h"
#include "world/area/kpa/kpa_100.h"
#include "world/area/kpa/kpa_52.h"

EvtScript EVS_ExitDoors_kpa_52_2 =
    EVT_EXIT_DOUBLE_DOOR($SplitLevelHall, $kpa_52.KeyTimingPuzzle, COLLIDER_ttw, MODEL_o160, MODEL_o159);
EvtScript EVS_ExitWalk_kpa_100_0 = EVT_EXIT_WALK(40, $KeyRoom, $kpa_100.KeyTimingPuzzle);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_52_2, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_100_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($SplitLevelHall.index)
            Set(LVar0, $SplitLevelHall.index)
            Set(LVar2, MODEL_o160)
            Set(LVar3, MODEL_o159)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($KeyRoom.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
