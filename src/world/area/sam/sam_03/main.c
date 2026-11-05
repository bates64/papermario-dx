#include "sam_03.h"
#include "world/area/sam/sam_04.h"
#include "world/area/sam/sam_11.h"
#include "effects.h"

EvtScript EVS_ExitWalk_sam_11_1 = EVT_EXIT_WALK(60, $PondArea, $sam_11.SnowfieldRoad);
EvtScript EVS_ExitWalk_sam_04_0 = EVT_EXIT_WALK(60, $ShiverSnowfield, $sam_04.SnowfieldRoad);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_11_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sam_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GF_MAP_ShiverSnowfield, true)
    Call(EnableModel, MODEL_o44, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o44, COLLIDER_FLAGS_UPPER_MASK)
    IfLt(GB_StoryProgress, STORY_CH7_STAR_SPIRIT_DEPARTED)
        Call(MakeNpcs, false, BeforeNPCs)
    Else
        Call(MakeNpcs, false, AfterNPCs)
    EndIf
    ExecWait(EVS_SetupMusic)
    PlayEffect(EFFECT_SNOWFALL, 0, 32)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_road, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_SNOW)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
