#include "arn_04.h"
#include "world/area/arn/arn_02.h"
#include "world/area/dgb/dgb_00.h"

EvtScript EVS_ExitWalk_arn_02_1 = EVT_EXIT_WALK(60, $Arn02, $arn_02.Arn04);
EvtScript EVS_ExitWalk_dgb_00_0 = EVT_EXIT_WALK(60, $TubbasManor, $dgb_00.GustyGulch);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_arn_02_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_dgb_00_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GUSTY_GULCH)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
