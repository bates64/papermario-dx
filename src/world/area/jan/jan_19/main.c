#include "jan_19.h"
#include "world/area/jan/jan_18.h"
#include "world/area/jan/jan_23.h"

EvtScript EVS_ExitWalk_jan_18_1 = EVT_EXIT_WALK(60, $Jan18, $jan_18.Jan19);
EvtScript EVS_ExitWalk_jan_23_0 = EVT_EXIT_WALK(60, $Jan23, $jan_23.Jan19);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_18_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_23_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    ExecWait(EVS_SetupMusic)
    Return
    End
};
