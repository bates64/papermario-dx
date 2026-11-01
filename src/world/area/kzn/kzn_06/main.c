#include "kzn_06.h"
#include "world/area/kzn/kzn_05.h"
#include "world/area/kzn/kzn_07.h"
#include "world/area/kzn/kzn_08.h"

EvtScript EVS_ExitWalk_kzn_05 = EVT_EXIT_WALK(60, $Kzn05, $kzn_05.Kzn06);
EvtScript EVS_ExitWalk_kzn_08 = EVT_EXIT_WALK(60, $Kzn08, $kzn_08.Kzn06);
EvtScript EVS_ExitWalk_kzn_07 = EVT_EXIT_WALK(60, $Kzn07, $kzn_07.Kzn06);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_05, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_08, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_07, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_StartTexPanners = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTexPanner, MODEL_yo1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o349, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(   0, -400,   0,   0)
        TEX_PAN_PARAMS_FREQ(   0,    1,   0,   0)
        TEX_PAN_PARAMS_INIT(   0,    0,   0,   0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_yougan, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_spot, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( 400,   0, 800,   0)
        TEX_PAN_PARAMS_FREQ(   1,   0,   1,   0)
        TEX_PAN_PARAMS_INIT(   0,   0,   0,   0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o250, .pos = $LavaReset_o250.pos },
    { .colliderID = COLLIDER_o468, .pos = $LavaReset_o468.pos },
    { .colliderID = COLLIDER_o394, .pos = $LavaReset_o394.pos },
    { .colliderID = COLLIDER_o440, .pos = $LavaReset_o440.pos },
    { .colliderID = COLLIDER_o437, .pos = $LavaReset_o437.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_06)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(GF_KZN06_Visited, true)
    ExecWait(EVS_MakeEntities)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    IfLt(GB_StoryProgress, STORY_CH5_LAVA_STREAM_BLOCKED)
        Call(PlayAmbientSounds, AMBIENT_LAVA_2)
    Else
        Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_yougan, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_yougan1, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    Exec(EVS_StartTexPanners)
    Exec(EVS_SetupLavaPuzzle)
    Return
    End
};
