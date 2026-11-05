#include "arn_02.h"
#include "world/area/arn/arn_04.h"
#include "world/area/arn/arn_05.h"

EvtScript EVS_ExitWalk_arn_05_1 = EVT_EXIT_WALK(60, $Arn05, $arn_05.Arn02);
EvtScript EVS_ExitWalk_arn_04_0 = EVT_EXIT_WALK(60, $Arn04, $arn_04.Arn02);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_arn_05_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_arn_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
