#include "omo_11.h"
#include "world/area/omo/omo_10.h"
#include "world/area/omo/omo_12.h"

EvtScript EVS_ExitWalk_omo_12_0 = EVT_EXIT_WALK(60, $Omo12, $omo_12.Omo11);
EvtScript EVS_ExitWalk_omo_10_0 = EVT_EXIT_WALK(60, $Omo10, $omo_10.Omo11);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_10_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupGizmos)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
