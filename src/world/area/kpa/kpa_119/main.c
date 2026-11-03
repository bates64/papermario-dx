#include "kpa_119.h"
#include "world/area/kpa/kpa_118.h"
#include "sprite.h"

EvtScript EVS_ExitWalk_kpa_118_1 = EVT_EXIT_WALK(60, $HiddenPassage3, $kpa_118.HiddenKeyRoom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_118_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deiliwtt, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
