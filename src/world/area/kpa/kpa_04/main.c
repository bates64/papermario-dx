#include "kpa_04.h"
#include "world/area/kpa/kpa_03.h"
#include "world/area/kpa/kpa_81.h"

EvtScript EVS_ExitWalk_kpa_03_1 = EVT_EXIT_WALK(60, $DarkCave2, $kpa_03.CaveExit);
EvtScript EVS_ExitWalk_kpa_81_3 = EVT_EXIT_WALK(60, $GuardDoor1, $kpa_81.CaveExit);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_81_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Exec(EVS_SetupStatues)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
