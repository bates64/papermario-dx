#include "flo_16.h"
#include "effects.h"

#include "world/common/atomic/TexturePan.inc.c"

API_CALLABLE(N(SpawnSunEffect)) {
    fx_sun(FX_SUN_FROM_RIGHT, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_flo_00_4) = EVT_EXIT_WALK(60, flo_16_ENTRY_0, "flo_00", flo_00_ENTRY_4);
EvtScript N(EVS_ExitWalk_flo_17_0) = EVT_EXIT_WALK(60, flo_16_ENTRY_1, "flo_17", flo_17_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_flo_00_4)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_flo_17_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

LavaReset N(SafeFloorColliders)[] = {
    { .colliderID = COLLIDER_o190, .pos = { -310.0,    0.0,    0.0 }},
    { .colliderID = COLLIDER_o191, .pos = {  305.0,  100.0,    0.0 }},
    { .colliderID = NO_COLLIDER }
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupVines))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o174, SURFACE_TYPE_SPIKES)
    Thread
        Call(ResetFromLava, Ref(N(SafeFloorColliders)))
    EndThread
    // vines scrolling left
    Call(SetTexPanner, MODEL_o59, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o142, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o58, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o136, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o146, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o139, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o143, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  140,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // vines scrolling right
    Call(SetTexPanner, MODEL_o135, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o138, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o140, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -200,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Exec(N(EVS_SetupPillarPuzzle))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    ExecWait(N(EVS_SetupMusic))
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(N(SpawnSunEffect))
    EndIf
    Return
    End
};
