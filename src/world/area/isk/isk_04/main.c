#include "isk_04.h"
#include "world/area/isk/isk_03.h"
#include "world/area/isk/isk_05.h"
#include "world/area/isk/isk_06.h"
#include "world/area/isk/isk_07.h"

s32 adjust_cam_on_landing(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (gPlayerStatus.pos.y > 25.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    }

    return ret;
}

API_CALLABLE(SetupLandingCamAdjust) {
    phys_set_landing_adjust_cam_check(adjust_cam_on_landing);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_isk_03_2 = EVT_EXIT_WALK(40, $SandDrainage1, $isk_03.DescendingStairs1);
EvtScript EVS_ExitWalk_isk_07_1 = EVT_EXIT_WALK(40, $SarcophagusHall2, $isk_07.DescendingStairs1);
EvtScript EVS_ExitWalk_isk_06_0 = EVT_EXIT_WALK(40, $SandDrainage2Upper, $isk_06.DescendingStairs1Upper);
EvtScript EVS_ExitWalk_isk_06_1 = EVT_EXIT_WALK(40, $SandDrainage2Lower, $isk_06.DescendingStairs1Lower);
EvtScript EVS_ExitWalk_isk_05_0 = EVT_EXIT_WALK(40, $PyramidStoneRoom, $isk_05.DescendingStairs1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_isk_03_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_07_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_06_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_06_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Call(SetupLandingCamAdjust)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(EVS_SetupObstructions)
        ExecWait(EVS_SetupDemo)
        Return
    EndIf
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupObstructions)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
