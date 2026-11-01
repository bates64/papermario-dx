#include "omo_01.h"
#include "world/area/omo/omo_13.h"

EvtScript EVS_ExitWalk_omo_13_0 = EVT_EXIT_WALK(60, $Omo13, $omo_13.Omo01);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_13_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_ShyGuysToybox, true)
    Set(GF_OMO01_Visited, true)
    Set(GF_MAC01_CalculatorStolen, true)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    ExecWait(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
