#include "kpa_101.h"
#include "world/area/kpa/kpa_09.h"

export s32 map_init(void) {
    use_map_geometry("kpa_119");
    return false;
}

EvtScript EVS_ExitWalk_kpa_09_0 = EVT_EXIT_WALK(60, $ShroomTimingPuzzle, $kpa_09.ShroomRoom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_09_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deiliwtt, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
