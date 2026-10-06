#include "kpa_111.h"

EvtScript EVS_ExitDoors_kpa_130_1 = EVT_EXIT_DOUBLE_DOOR(kpa_111_ENTRY_0, "kpa_130", kpa_130_ENTRY_1, COLLIDER_deiliwtt, MODEL_o119, MODEL_o118);
EvtScript EVS_ExitDoors_kpa_112_0 = EVT_EXIT_WALK(40, kpa_111_ENTRY_1, "kpa_112", kpa_112_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_kpa_130_1), TRIGGER_WALL_PRESS_A, COLLIDER_deiliwtt, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_kpa_112_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kpa_111_ENTRY_0)
            Set(LVar0, kpa_111_ENTRY_0)
            Set(LVar2, MODEL_o119)
            Set(LVar3, MODEL_o118)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(kpa_111_ENTRY_1)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
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
    Return
    End
};
