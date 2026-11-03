#include "kpa_118.h"
#include "world/area/kpa/kpa_115.h"
#include "world/area/kpa/kpa_119.h"

EvtScript EVS_ExitWalk_kpa_115_2 = EVT_EXIT_WALK(60, $HiddenDoorRoom3, $kpa_115.HiddenPassage3);
EvtScript EVS_ExitWalk_kpa_119_0 = EVT_EXIT_WALK(60, $HiddenKeyRoom, $kpa_119.HiddenPassage3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_115_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_119_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
