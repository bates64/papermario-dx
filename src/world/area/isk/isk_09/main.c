#include "isk_09.h"

s32 adjust_cam_on_landing(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (gPlayerStatus.pos.y > -90.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    } else if (gPlayerStatus.pos.y < -370.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    }

    return ret;
}

API_CALLABLE(SetupLandingCamAdjust) {
    phys_set_landing_adjust_cam_check(adjust_cam_on_landing);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_isk_08_0 = EVT_EXIT_WALK(40, isk_09_ENTRY_0, "isk_08", isk_08_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_isk_08_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_09)
    Call(SetupLandingCamAdjust)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupSwitches)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupStairs)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};
