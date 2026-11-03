#include "kpa_115.h"
#include "world/area/kpa/kpa_114.h"
#include "world/area/kpa/kpa_116.h"
#include "world/area/kpa/kpa_118.h"

EvtScript EVS_ExitWalk_kpa_114_1 = EVT_EXIT_WALK(60, $HiddenPassage2, $kpa_114.HiddenDoorRoom3);
EvtScript EVS_ExitWalk_kpa_116_0 = EVT_EXIT_WALK(60, $DeadEndPassage, $kpa_116.HiddenDoorRoom3);
EvtScript EVS_ExitWalk_kpa_118_0 = EVT_EXIT_WALK(60, $HiddenPassage3, $kpa_118.HiddenDoorRoom3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_114_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_118_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_116_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    Exec(EVS_SetupStatues)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
