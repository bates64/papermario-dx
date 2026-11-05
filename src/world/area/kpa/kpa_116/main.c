#include "kpa_116.h"
#include "world/area/kpa/kpa_115.h"
#include "world/area/kpa/kpa_117.h"

EvtScript EVS_ExitWalk_kpa_115_1 = EVT_EXIT_WALK(60, $HiddenDoorRoom3, $kpa_115.DeadEndPassage);
EvtScript EVS_ExitWalk_kpa_117_0 = EVT_EXIT_WALK(60, $DeadEndRoom, $kpa_117.DeadEndPassage);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_115_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_117_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
