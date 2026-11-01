#include "omo_13.h"
#include "world/area/omo/omo_01.h"
#include "world/area/omo/omo_03.h"

EvtScript EVS_ExitWalk_omo_01_0 = EVT_EXIT_WALK(60, $Omo01, $omo_01.Omo13);
EvtScript EVS_ExitWalk_omo_03_0 = EVT_EXIT_WALK(60, $Omo03, $omo_03.Omo13);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfEq(GF_OMO13_Defeated_AntiGuy, true)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_he, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
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
