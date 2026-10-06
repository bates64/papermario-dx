#include "arn_02.h"

EvtScript EVS_ExitWalk_arn_05_1 = EVT_EXIT_WALK(60, arn_02_ENTRY_0, "arn_05", arn_05_ENTRY_1);
EvtScript EVS_ExitWalk_arn_04_0 = EVT_EXIT_WALK(60, arn_02_ENTRY_1, "arn_04", arn_04_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_arn_05_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_arn_04_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GUSTY_GULCH)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
