#include "flo_18.h"
#include "world/area/flo/flo_17.h"
#include "effects.h"

EvtScript EVS_ExitWalk_flo_17_1 = EVT_EXIT_WALK(60, $Flo17, $flo_17.Flo18);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_17_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o138, .pos = $LavaReset_o138.pos },
    { .colliderID = COLLIDER_o140, .pos = $LavaReset_o140.pos },
    { .colliderID = COLLIDER_o142, .pos = $LavaReset_o142.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_SetupFoliage)
    Exec(EVS_SetupMachine)
    Exec(EVS_SetupMachineDamageReactions)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o44, SURFACE_TYPE_SPIKES)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    Call(SetTexPanner, MODEL_o48, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o50, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o52, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o54, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o58, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o60, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -140,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_o49, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o51, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o53, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o57, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o59, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -200,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Flo17.index)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
        Exec(EVS_Scene_LakilesterLikesBeingGood)
        Exec(EVS_BindExitTriggers)
    EndIf
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Return
    End
};
