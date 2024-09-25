#include "isk_09.h"

s32 N(adjust_cam_on_landing)(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (gPlayerStatus.pos.y > -90.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    } else if (gPlayerStatus.pos.y < -370.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    }

    return ret;
}

API_CALLABLE(N(SetupLandingCamAdjust)) {
    phys_set_landing_adjust_cam_check(N(adjust_cam_on_landing));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_isk_08_0) = EVT_EXIT_WALK(40, isk_09_ENTRY_0, "isk_08", isk_08_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_isk_08_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_09)
    Call(N(SetupLandingCamAdjust))
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupSwitches))
    Exec(N(EVS_SetupMusic))
    ExecWait(N(EVS_SetupStairs))
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Return
    End
};
