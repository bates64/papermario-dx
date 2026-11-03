#include "sam_05.h"
#include "world/area/sam/sam_04.h"
#include "world/area/sam/sam_06.h"
#include "effects.h"

EvtScript EVS_ExitWalk_sam_04_1 = EVT_EXIT_WALK(60, $ShiverSnowfield, $sam_04.StarbornPath);
EvtScript EVS_ExitWalk_sam_06_0 = EVT_EXIT_WALK(60, $StarbornValley, $sam_06.StarbornPath);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_04_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sam_06_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHIVER_SNOWFIELD)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH7_DEFEATED_MONSTAR)
        Call(MakeNpcs, false, BeforeNPCs)
    Else
        Call(MakeNpcs, false, AfterNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    PlayEffect(EFFECT_SNOWFALL, 0, 120)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_ground, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o55, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o59, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o60, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_SNOW)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
