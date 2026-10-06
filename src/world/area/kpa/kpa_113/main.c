#include "kpa_113.h"

EvtScript EVS_ExitWalk_kpa_112_1 = EVT_EXIT_WALK(40, kpa_113_ENTRY_0, "kpa_112", kpa_112_ENTRY_1);
EvtScript EVS_ExitWalk_kpa_114_0 = EVT_EXIT_WALK(40, kpa_113_ENTRY_2, "kpa_114", kpa_114_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kpa_112_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_kpa_114_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
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
    IfEq(LVar0, kpa_113_ENTRY_1)
        Set(LVar2, MODEL_o136)
        Set(LVar3, MODEL_o137)
        ExecWait(EnterDoubleDoor)
        Exec(EVS_BindExitTriggers)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupStatues)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
