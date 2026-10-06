#include "jan_17.h"

API_CALLABLE(EnableFog) {
    enable_world_fog();
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_jan_16_2 = EVT_EXIT_WALK(60, jan_17_ENTRY_0, "jan_16", jan_16_ENTRY_2);
EvtScript EVS_ExitWalk_jan_18_0 = EVT_EXIT_WALK(60, jan_17_ENTRY_1, "jan_18", jan_18_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_jan_16_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_jan_18_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_JAN_17)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(EnableFog)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Wait(1)
    ExecWait(EVS_SetupMusic)
    Return
    End
};
