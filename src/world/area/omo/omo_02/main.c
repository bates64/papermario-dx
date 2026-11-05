#include "omo_02.h"
#include "world/area/omo/omo_10.h"
#include "world/area/omo/omo_14.h"

EvtScript EVS_ExitWalk_omo_10_1 = EVT_EXIT_WALK(60, $Omo10, $omo_10.Omo02);
EvtScript EVS_ExitWalk_omo_14_0 = EVT_EXIT_WALK(60, $Omo14, $omo_14.Omo02);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_10_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_14_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupBarricade)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
