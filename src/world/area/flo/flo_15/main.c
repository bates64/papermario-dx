#include "flo_15.h"

EvtScript EVS_ExitWalk_flo_13_1 = EVT_EXIT_WALK(60, flo_15_ENTRY_0, "flo_13", flo_13_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_flo_13_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, flo_15_ENTRY_1)
        Exec(EVS_Scene_SunReturns)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_g58, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_MonitorFallingStairs)
    ExecWait(EVS_SetupMusic)
    Return
    End
};
