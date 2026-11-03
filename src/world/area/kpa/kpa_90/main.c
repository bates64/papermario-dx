#include "kpa_90.h"
#include "world/area/kpa/kpa_32.h"
#include "world/area/kpa/kpa_91.h"

EvtScript EVS_ExitWalk_kpa_91_0 = EVT_EXIT_WALK(60, $EastUpperJail, $kpa_91.EastJailStairs);
EvtScript EVS_ExitWalk_kpa_32_1 = EVT_EXIT_WALK(60, $LowerGrandHall, $kpa_32.EastJailStairs);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_91_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_32_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
