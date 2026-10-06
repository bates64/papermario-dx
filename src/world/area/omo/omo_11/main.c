#include "omo_11.h"

EvtScript EVS_ExitWalk_omo_12_0 = EVT_EXIT_WALK(60, omo_11_ENTRY_0, "omo_12", omo_12_ENTRY_0);
EvtScript EVS_ExitWalk_omo_10_0 = EVT_EXIT_WALK(60, omo_11_ENTRY_1, "omo_10", omo_10_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_omo_12_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_omo_10_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupGizmos)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
