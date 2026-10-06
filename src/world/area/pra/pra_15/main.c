#include "pra_15.h"

API_CALLABLE(DisableTotalFloorReflections) {
    gOverrideFlags &= ~GLOBAL_OVERRIDES_ENABLE_FLOOR_REFLECTION;
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_pra_01_3 = EVT_EXIT_WALK(60, pra_15_ENTRY_0, "pra_01", pra_01_ENTRY_3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_pra_01_3), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_15_ENTRY_0)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1298, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    Call(DisableTotalFloorReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
