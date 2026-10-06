#include "kpa_118.h"

EvtScript EVS_ExitWalk_kpa_115_2 = EVT_EXIT_WALK(60, kpa_118_ENTRY_0, "kpa_115", kpa_115_ENTRY_2);
EvtScript EVS_ExitWalk_kpa_119_0 = EVT_EXIT_WALK(60, kpa_118_ENTRY_1, "kpa_119", kpa_119_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kpa_115_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_kpa_119_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
