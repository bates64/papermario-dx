#include "jan_17.h"
#include "world/area/jan/jan_16.h"
#include "world/area/jan/jan_18.h"

EvtScript EVS_ExitWalk_jan_16_2 = EVT_EXIT_WALK(60, $Jan16, $jan_16.Jan17);
EvtScript EVS_ExitWalk_jan_18_0 = EVT_EXIT_WALK(60, $Jan18, $jan_18.Jan17);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_16_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_18_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    Wait(1)
    ExecWait(EVS_SetupMusic)
    Return
    End
};
