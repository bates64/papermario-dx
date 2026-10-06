#include "flo_10.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

EvtScript EVS_ExitWalk_flo_24_1 = EVT_EXIT_WALK(60, flo_10_ENTRY_0, "flo_24", flo_24_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_flo_24_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupFoliage)
    Exec(EVS_SetupWaterStoneSocket)
    Exec(EVS_SetupFountain)
    Exec(EVS_SetupWaterEffect)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o80, SURFACE_TYPE_FLOWERS)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o93, SURFACE_TYPE_FLOWERS)
    EVT_FLOWER_SPAWN_REGION( -265,  247,  199,  313,  0)
    EVT_FLOWER_SPAWN_REGION( -300, -275, -140, -185,  0)
    EVT_FLOWER_SPAWN_REGION(  263, -248,  362,  146,  0)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(flo_10_ENTRY_1)
            Exec(EVS_Scene_SunReturns)
        CaseEq(flo_10_ENTRY_2)
            Exec(EVS_Scene_PostReleaseFountain)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Return
    End
};
