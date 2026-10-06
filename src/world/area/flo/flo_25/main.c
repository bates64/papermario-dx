#include "flo_25.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

EvtScript EVS_ExitWalk_flo_00_3 = EVT_EXIT_WALK(60, flo_25_ENTRY_0, "flo_00", flo_00_ENTRY_3);
EvtScript EVS_ExitWalk_flo_07_0 = EVT_EXIT_WALK(60, flo_25_ENTRY_1, "flo_07", flo_07_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_flo_07_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_flo_00_3), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupVines)
    Exec(EVS_SetupFoliage)
    EVT_FLOWER_SPAWN_REGION( -270, -190,  640,  -60, 60)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    EndIf
    Return
    End
};
