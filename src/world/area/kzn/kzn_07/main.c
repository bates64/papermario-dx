#include "kzn_07.h"
#include "model.h"

#include "../common/LavaGlowLighting.inc.c"

ModelIDList LavaModelIDs = {
    .count = 1,
    .list = { MODEL_yougan }
};

EvtScript EVS_ExitWalk_kzn_06 = EVT_EXIT_WALK(60, kzn_07_ENTRY_0, "kzn_06", kzn_06_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_06, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_SetupTexPanners = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTexPanner, MODEL_yougan,  TEX_PANNER_0)
    Call(SetTexPanner, MODEL_yougan1, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_spot,    TEX_PANNER_1)
    Call(SetTexPanner, MODEL_yougan2, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_sara,    TEX_PANNER_1)
    Call(SetTexPanner, MODEL_chioro,  TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP( -400,    0, -800,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0, -400,    0, -800)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o365, .pos = {  120.0, 0.0, 100.0 }},
    { .colliderID = COLLIDER_o411, .pos = { -120.0, 0.0, 100.0 }},
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_07)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_doro, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, Ref(SafeFloorColliders))
    EndThread
    Exec(EVS_SetupTexPanners)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Thread
        SetGroup(EVT_GROUP_NEVER_PAUSE)
        Call(ApplyLavaGlowLighting, LAVA_GLOW_MODE_0, nullptr)
    EndThread
    Thread
        Call(ClearLavaGlowLighting, Ref(LavaModelIDs))
    EndThread
    Return
    End
};
