
#include "kpa_52.h"
#include "world/area/kpa/kpa_08.h"
#include "world/area/kpa/kpa_33.h"
#include "world/area/kpa/kpa_40.h"

EvtScript EVS_ExitDoors_kpa_33_2 =
    EVT_EXIT_DOUBLE_DOOR($UpperGrandHall, $kpa_33.SplitLevelHall, COLLIDER_ttw, MODEL_o407, MODEL_o408);
EvtScript EVS_ExitDoors_kpa_40_0 =
    EVT_EXIT_DOUBLE_DOOR($MazeGuideRoom, $kpa_40.SplitLevelHall, COLLIDER_tte1, MODEL_o410, MODEL_o409);
EvtScript EVS_ExitDoors_kpa_08_0 =
    EVT_EXIT_DOUBLE_DOOR($KeyTimingPuzzle, $kpa_08.SplitLevelHall, COLLIDER_tte2, MODEL_o412, MODEL_o411);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_33_2, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_08_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte2, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($UpperGrandHall.index)
            Set(LVar0, $UpperGrandHall.index)
            Set(LVar2, MODEL_o407)
            Set(LVar3, MODEL_o408)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($MazeGuideRoom.index)
            Set(LVar0, 1)
            Set(LVar2, MODEL_o410)
            Set(LVar3, MODEL_o409)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($KeyTimingPuzzle.index)
            Set(LVar0, 2)
            Set(LVar2, MODEL_o412)
            Set(LVar3, MODEL_o411)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
