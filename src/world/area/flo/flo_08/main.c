#include "flo_08.h"
#include "world/area/flo/flo_00.h"
#include "world/area/flo/flo_24.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

EvtScript EVS_ExitWalk_flo_00_6 = EVT_EXIT_WALK(60, $Flo00, $flo_00.Flo08);
EvtScript EVS_ExitWalk_flo_24_0 = EVT_EXIT_WALK(60, $Flo24, $flo_24.Flo08);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_00_6, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_flo_24_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o158, .pos = $LavaReset_o158.pos },
    { .colliderID = COLLIDER_o132, .pos = $LavaReset_o132.pos },
    { .colliderID = COLLIDER_o223, .pos = $LavaReset_o223.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupVines)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o114, SURFACE_TYPE_SPIKES)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    // vines
    Call(SetTexPanner, MODEL_o25, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o27, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o31, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o33, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o35, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o37, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  140,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_o28, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o32, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o34, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o36, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_o38, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -200,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o129, SURFACE_TYPE_FLOWERS)
    EVT_FLOWER_SPAWN_REGION(140, -137, 340, -60, 0)
    EVT_FLOWER_SPAWN_REGION(450, -137, 590, -60, 0)
    Exec(EVS_SetupFoliage)
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
