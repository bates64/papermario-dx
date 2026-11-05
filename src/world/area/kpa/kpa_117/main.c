#include "kpa_117.h"
#include "world/area/kpa/kpa_116.h"

EvtScript EVS_Empty = {
    Return
    End
};

EvtScript EVS_ExitWalk_kpa_116_1 = EVT_EXIT_WALK(60, $DeadEndPassage, $kpa_116.DeadEndRoom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_116_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_Empty)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
