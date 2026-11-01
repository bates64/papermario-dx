#include "jan_18.h"
#include "world/area/jan/jan_17.h"
#include "world/area/jan/jan_19.h"

EvtScript EVS_ExitWalk_jan_17_1 = EVT_EXIT_WALK(60, $Jan17, $jan_17.Jan18);
EvtScript EVS_ExitWalk_jan_19_0 = EVT_EXIT_WALK(60, $Jan19, $jan_19.Jan18);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_17_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_19_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitse, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    ExecWait(EVS_SetupMusic)
    Return
    End
};
