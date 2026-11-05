#include "flo_22.h"
#include "world/area/flo/flo_03.h"
#include "effects.h"

EvtScript EVS_ExitWalk_flo_03_1 = EVT_EXIT_WALK(60, $Flo03, $flo_03.Flo22);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_SetupFoliage)
    Exec(EVS_SetupWell)
    Call(GetEntryID, LVar0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_SniffleHint)
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Return
    End
};
