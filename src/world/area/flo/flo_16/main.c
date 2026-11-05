#include "flo_16.h"
#include "world/area/flo/flo_00.h"
#include "world/area/flo/flo_17.h"
#include "effects.h"

EvtScript EVS_ExitWalk_flo_00_4 = EVT_EXIT_WALK(60, $Flo00, $flo_00.Flo16);
EvtScript EVS_ExitWalk_flo_17_0 = EVT_EXIT_WALK(60, $Flo17, $flo_17.Flo16);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_00_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_flo_17_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o190, .pos = $LavaReset_o190.pos },
    { .colliderID = COLLIDER_o191, .pos = $LavaReset_o191.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupVines)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o174, SURFACE_TYPE_SPIKES)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
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
        Exec(EVS_UpdateTexturePan)
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
        Exec(EVS_UpdateTexturePan)
    EndThread
    Exec(EVS_SetupPillarPuzzle)
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
