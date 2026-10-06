#include "isk_01.h"

s32 adjust_cam_on_landing(void) {
    return LANDING_CAM_ALWAYS_ADJUST;
}

API_CALLABLE(SetupLandingCamAdjust) {
    phys_set_landing_adjust_cam_check(adjust_cam_on_landing);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_sbk_02_4 = EVT_EXIT_WALK(40, isk_01_ENTRY_0, "sbk_02", sbk_02_ENTRY_4);
EvtScript EVS_ExitWalk_isk_02_0 = EVT_EXIT_WALK(40, isk_01_ENTRY_1, "isk_02", isk_02_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sbk_02_4), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_isk_02_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetupLandingCamAdjust)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_DryDryRuins, true)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupHaze)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
