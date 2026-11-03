#include "flo_09.h"
#include "world/area/flo/flo_00.h"
#include "world/area/flo/flo_03.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

EvtScript EVS_ExitWalk_flo_00_5 = EVT_EXIT_WALK(60, $Flo00, $flo_00.Flo09);
EvtScript EVS_ExitWalk_flo_03_0 = EVT_EXIT_WALK(60, $Flo03, $flo_03.Flo09);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_00_5, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_flo_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_SetupVines)
    Exec(EVS_SetupFoliage)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o104, SURFACE_TYPE_FLOWERS)
    EVT_FLOWER_SPAWN_REGION( -511,   -4, -319,   10,  0)
    EVT_FLOWER_SPAWN_REGION( -302,   77,  -32,  116,  0)
    EVT_FLOWER_SPAWN_REGION(   51,   18,  141,  127,  0)
    EVT_FLOWER_SPAWN_REGION(  234,   38,  502,   98,  0)
    EVT_FLOWER_SPAWN_REGION( -525, -163, -400,  -80, 60)
    EVT_FLOWER_SPAWN_REGION( -346, -148,  517,  -91, 60)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Return
    End
};
