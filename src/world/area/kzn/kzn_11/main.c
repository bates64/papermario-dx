#include "kzn_11.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_kzn_10_1) = EVT_EXIT_WALK(60, kzn_11_ENTRY_0, "kzn_10", kzn_10_ENTRY_1);
EvtScript N(EVS_ExitWalk_kzn_17_0) = EVT_EXIT_WALK(60, kzn_11_ENTRY_1, "kzn_17", kzn_17_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_10_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_17_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript N(EVS_StartTexPanners) = {
    // lava surfaces
    Call(SetTexPanner, MODEL_yougan1_1, TEX_PANNER_2)
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
        TEX_PAN_PARAMS_MAX(0x40000)
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
    { .colliderID = COLLIDER_o80,  .pos = { -760.0, 20.0, 0.0 }},
    { .colliderID = COLLIDER_o211, .pos = { -400.0, 20.0, 0.0 }},
    { .colliderID = COLLIDER_o212, .pos = {  230.0, 20.0, 0.0 }},
    { .colliderID = COLLIDER_o83,  .pos = {  790.0, 20.0, 0.0 }},
    { .colliderID = NO_COLLIDER }
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_11)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o175, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o176, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o177, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o178, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o156, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o179, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o180, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o181, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_pp1, SURFACE_TYPE_LAVA)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_pp2, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, Ref(N(SafeFloorColliders)))
    EndThread
    Exec(N(EVS_StartTexPanners))
    Exec(N(EVS_UpdateLeftPlatform))
    Exec(N(EVS_UpdateRightPlatform))
    Return
    End
};
