#include "kzn_08.h"
#include "world/area/kzn/kzn_06.h"
#include "model.h"

#include "../common/LavaGlowLighting.inc.c"

EvtScript EVS_StartTexPanners = {
    // background lava fall
    Call(SetTexPanner, MODEL_yougan1, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(   0, -800,   0,   0)
        TEX_PAN_PARAMS_FREQ(   0,    1,   0,   0)
        TEX_PAN_PARAMS_INIT(   0,    0,   0,   0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // lava channel
    Call(SetTexPanner, MODEL_yougan, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o640, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( 800,   0, 1600,   0)
        TEX_PAN_PARAMS_FREQ(   1,   0,    1,   0)
        TEX_PAN_PARAMS_INIT(   0,   0,    0,   0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_kem2, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP( 500,    0,    0, -400)
        TEX_PAN_PARAMS_FREQ(   1,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

ModelIDList LavaModelIDs = {
    .count = 1,
    .list = { MODEL_yougan }
};

EvtScript EVS_ExitWalk_kzn_06 = EVT_EXIT_WALK(60, $Kzn06, $kzn_06.Kzn08);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_06, TRIGGER_FLOOR_TOUCH, COLLIDER_deili1, 1, 0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o468, .pos = $LavaReset_o468.pos },
    { .colliderID = COLLIDER_o470, .pos = $LavaReset_o470.pos },
    { .colliderID = COLLIDER_o322, .pos = $LavaReset_o322.pos },
    { .colliderID = COLLIDER_o446, .pos = $LavaReset_o446.pos },
    { .colliderID = COLLIDER_o454, .pos = $LavaReset_o454.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_AnimateLavaScale = {
    Call(DisablePlayerInput, true)
    Call(MakeLerp, 1, 100, 200, EASING_LINEAR)
    Label(0)
        Call(UpdateLerp)
        DivF(LVar0, 10.0)
        Call(ScaleModel, MODEL_yougan1, LVar0, 1.0, 1.0)
        MulF(LVar0, -5.0)
        AddF(LVar0, 100.0)
        Set(MV_GlowIntensity, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Call(MakeLerp, 0, 35, 100, EASING_LINEAR)
    Label(10)
        Call(UpdateLerp)
        Call(TranslateModel, MODEL_yougan, 0, LVar0, 0)
        MulF(LVar0, -1.25)
        AddF(LVar0, 50.0)
        Set(MV_GlowIntensity, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(10)
        EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS,  COLLIDER_yougan_atari, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_yougan_atari, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    Call(DisablePlayerInput, false)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_08)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_UpdateLavaRoomDarkness)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_yougan_atari, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, SafeFloorColliders)
    EndThread
    Call(ScaleModel, MODEL_yougan1, 10.0, 1.0, 1.0)
    Call(TranslateModel, MODEL_yougan, 0, 40, 0)
    Set(MV_GlowIntensity, 0)
    Thread
        SetGroup(EVT_GROUP_NEVER_PAUSE)
        Call(ApplyLavaGlowLighting, LAVA_GLOW_MODE_2, nullptr)
    EndThread
    Thread
        Call(ClearLavaGlowLighting, LavaModelIDs)
    EndThread
    Exec(EVS_StartTexPanners)
    Return
    End
};
