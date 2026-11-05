
#include "sam_09.h"
#include "world/area/sam/sam_08.h"
#include "world/area/sam/sam_10.h"

EvtScript EVS_ExitWalk_sam_08_1 = EVT_EXIT_WALK(60, $MountainHills, $sam_08.MountainTunnel);
EvtScript EVS_ExitWalk_sam_10_0 = EVT_EXIT_WALK(60, $MountainPeaks, $sam_10.MountainTunnel);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_08_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sam_10_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_yuka, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    ExecWait(EVS_SetupSockets)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
