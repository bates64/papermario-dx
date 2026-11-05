#include "kpa_113.h"
#include "world/area/kpa/kpa_112.h"
#include "world/area/kpa/kpa_114.h"

EvtScript EVS_ExitWalk_kpa_112_1 = EVT_EXIT_WALK(40, $HiddenPassage1, $kpa_112.HiddenDoorRoom2);
EvtScript EVS_ExitWalk_kpa_114_0 = EVT_EXIT_WALK(40, $HiddenPassage2, $kpa_114.HiddenDoorRoom2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_112_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_114_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar0)
    IfEq(LVar0, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $GuardDoor2.index)
        Set(LVar2, MODEL_o136)
        Set(LVar3, MODEL_o137)
        ExecWait(EnterDoubleDoor)
        Exec(EVS_BindExitTriggers)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupStatues)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
