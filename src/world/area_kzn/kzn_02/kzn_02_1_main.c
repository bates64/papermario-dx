#include "kzn_02.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_kzn_01_1) = EVT_EXIT_WALK(60, kzn_02_ENTRY_0, "kzn_01", kzn_01_ENTRY_1);
EvtScript N(EVS_ExitWalk_kzn_03_0) = EVT_EXIT_WALK(60, kzn_02_ENTRY_1, "kzn_03", kzn_03_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(N(EVS_ExitWalk_kzn_01_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(N(EVS_ExitWalk_kzn_03_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    IfNe(LVar0, kzn_02_ENTRY_2)
        Set(LVar0, N(EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript N(EVS_StartTexPanners) = {
    // lava surfaces
    Call(SetTexPanner, MODEL_yougan1_1, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_yougan1_2, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( 200,    0,  400, -100)
        TEX_PAN_PARAMS_FREQ(   1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // leaking lava
    Call(SetTexPanner, MODEL_toro, TEX_PANNER_5)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_5)
        TEX_PAN_PARAMS_STEP( 300, -500,    0,    0)
        TEX_PAN_PARAMS_FREQ(   1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // lava bubbles
    Call(SetTexPanner, MODEL_poko, TEX_PANNER_D)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_D)
        TEX_PAN_PARAMS_MAX(0x80000000)
        TEX_PAN_PARAMS_STEP(0x8000,  0,    0,    0)
        TEX_PAN_PARAMS_FREQ(   6,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_kem2, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP( 500,    0,    0, -400)
        TEX_PAN_PARAMS_FREQ(   1,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

LavaReset N(SafeFloorColliders)[] = {
    { .colliderID = COLLIDER_o80, .pos = { -790.0, 20.0,  0.0 }},
    { .colliderID = COLLIDER_o81, .pos = { -790.0, 20.0,  0.0 }},
    { .colliderID = COLLIDER_o58, .pos = { -250.0, 20.0,  0.0 }},
    { .colliderID = COLLIDER_o59, .pos = { -250.0, 20.0,  0.0 }},
    { .colliderID = COLLIDER_o77, .pos = {  250.0, 20.0, 15.0 }},
    { .colliderID = COLLIDER_o78, .pos = {  250.0, 20.0, 15.0 }},
    { .colliderID = COLLIDER_o83, .pos = {  790.0, 20.0,  0.0 }},
    { .colliderID = COLLIDER_o84, .pos = {  790.0, 20.0,  0.0 }},
    { .colliderID = NO_COLLIDER }
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_02)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o112, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o217, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o218, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o219, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o220, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o221, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o222, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_pp1, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_pp2, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, Ref(N(SafeFloorColliders)))
    EndThread
    Exec(N(EVS_StartTexPanners))
    ExecWait(N(EVS_InitializePlatforms))
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(N(EVS_PlayDemoScene))
        Return
    EndIf
    Exec(N(EVS_EnterMap))
    Wait(1)
    Call(SetMusicTrack, 0, SONG_MT_LAVALAVA, 0, 8)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Return
    End
};
