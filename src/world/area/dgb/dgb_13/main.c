#include "dgb_13.h"
#include "world/area/dgb/dgb_03.h"

EvtScript EVS_ExitWalk_dgb_03_5 = EVT_EXIT_WALK(26, $Dgb03, $dgb_03.Dgb13);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_dgb_03_5, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    ExecWait(EVS_SetupDrawers)
    Exec(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
