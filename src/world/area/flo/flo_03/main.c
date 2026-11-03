#include "flo_03.h"
#include "world/area/flo/flo_09.h"
#include "world/area/flo/flo_22.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

EvtScript EVS_ExitWalk_flo_09_1 = EVT_EXIT_WALK(60, $Flo09, $flo_09.Flo03);
EvtScript EVS_ExitWalk_flo_22_0 = EVT_EXIT_WALK(60, $Flo22, $flo_22.Flo03);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_09_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_flo_22_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(AF_FLO_TreeDrop_RedBerry1, false)
    Set(AF_FLO_TreeDrop_RedBerry2, false)
    Set(AB_FLO03_DialogueState_Petunia, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMoles)
    Exec(EVS_SetupFoliage)
    Exec(EVS_EmptyEntityHandler)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o160, SURFACE_TYPE_FLOWERS)
    EVT_FLOWER_SPAWN_REGION( -145, -335,  182, -180, 0)
    EVT_FLOWER_SPAWN_REGION(  200, -170,  310,  150, 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Flo12.index)
        Exec(EVS_Scene_SunReturns)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Return
    End
};
