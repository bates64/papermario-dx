#include "kpa_100.h"
#include "world/area/kpa/kpa_08.h"
#include "sprite.h"

export s32 map_init(void) {
    use_map_geometry("kpa_117");
    return false;
}

EvtScript EVS_ExitWalk_kpa_08_1 = EVT_EXIT_WALK(60, $KeyTimingPuzzle, $kpa_08.KeyRoom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_08_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
