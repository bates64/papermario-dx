#include "jan_02.h"
#include "effects.h"

extern s32 PrevPalmTreeVisibility;

API_CALLABLE(ClearTrackVols) {
    bgm_clear_track_volumes(0, TRACK_VOLS_JAN_FULL);
    return ApiStatus_DONE2;
}

API_CALLABLE(ManageBigPalmTreeVisibility) {
    u16 currentFloor = gCollisionStatus.curFloor;

    if (PrevPalmTreeVisibility != 0) {
        if (currentFloor == COLLIDER_o327 || currentFloor == COLLIDER_o330) {
            mdl_group_set_visibility(MODEL_g70, MODEL_FLAG_HIDDEN, MODEL_GROUP_HIDDEN);
            PrevPalmTreeVisibility = false;
        }
    } else {
        if (currentFloor == COLLIDER_o319 || currentFloor == COLLIDER_o316) {
            mdl_group_set_visibility(MODEL_g70, MODEL_FLAG_HIDDEN, MODEL_GROUP_VISIBLE);
            PrevPalmTreeVisibility = true;
        }
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_ExitWalk_jan_01_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(ClearTrackVols)
    Call(UseExitHeading, 60, jan_02_ENTRY_0)
    Exec(ExitWalk)
    Call(GotoMap, Ref("jan_01"), jan_01_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_jan_03_0 = EVT_EXIT_WALK(60, jan_02_ENTRY_1, "jan_03", jan_03_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_jan_01_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_jan_03_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

s32 PrevPalmTreeVisibility = true;

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_YOSHIS_VILLAGE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
#if VERSION_PAL
    Call(GetLanguage, LVar0)
    Call(SetModelTexVariant, MODEL_o120, LVar0)
#endif
    Set(GF_MAP_YoshisVillage, true)
    Set(AF_JAN02_RaphaelComment, false)
    Set(AF_JAN02_MetCouncillor, false)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupFoliage)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitnw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Exec(EVS_SetupMusic)
    Call(PlaySound, SOUND_LOOP_JAN_BEACH_WAVES)
    // waves
    Call(SetTexPanner, MODEL_o202, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o203, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0,  400,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water surface
    Call(SetTexPanner, MODEL_o103, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -100,  200,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        Call(ManageBigPalmTreeVisibility)
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o337, SURFACE_TYPE_WATER)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o338, SURFACE_TYPE_WATER)
    Return
    End
};
