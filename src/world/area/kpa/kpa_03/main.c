#include "kpa_03.h"
#include "world/area/kpa/kpa_01.h"
#include "world/area/kpa/kpa_04.h"

#include "world/common/util/CreateDarkness.inc.c"

EvtScript EVS_ExitWalk_kpa_01_1 = EVT_EXIT_WALK(60, $DarkCave1, $kpa_01.DarkCave2);
EvtScript EVS_ExitWalk_kpa_04_0 = EVT_EXIT_WALK(60, $CaveExit, $kpa_04.DarkCave2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_01_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
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
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_CreateDarkness)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
