#include "flo_19.h"
#include "effects.h"

EvtScript EVS_ExitWalk_flo_21_0 = EVT_EXIT_WALK(60, flo_19_ENTRY_1, "flo_21", flo_21_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_flo_21_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CLOUDY_CLIMB)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_CloudyClimb, true)
    ExecWait(EVS_MakeEntities)
    Call(ParentColliderToModel, COLLIDER_o117, MODEL_o142)
    Call(HidePlayerShadow, true)
    Exec(EVS_SetupBeanstalk)
    Exec(EVS_SetupClouds)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o122, SURFACE_TYPE_CLOUD)
    Call(SetTexPanner, MODEL_o59, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o60, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -120,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(  -90,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(GetEntryID, LVar0)
    IfNe(LVar0, flo_19_ENTRY_3)
        Set(AF_FLO_RidingBeanstalk, false)
    EndIf
    Switch(LVar0)
        CaseEq(flo_19_ENTRY_0)
            Exec(EVS_BindExitTriggers)
        CaseEq(flo_19_ENTRY_1)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
        CaseEq(flo_19_ENTRY_2)
            Exec(EVS_Scene_BeanstalkGrowing)
            Exec(EVS_BindExitTriggers)
        CaseEq(flo_19_ENTRY_3)
            Exec(EVS_Enter_Beanstalk)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Return
    End
};
