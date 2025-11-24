#include "iwa_00.h"

#include "world/common/atomic/TexturePan.inc.c"

b32 N(should_player_be_sliding)(void) {
    Shadow* shadow = get_shadow_by_index(gPlayerStatus.shadowID);
    f32 angle = shadow->rot.z + 180.0;

    return (angle != 0.0f) && (fabsf(angle) >= 20.0f);
}

API_CALLABLE(N(SetupSlidingCheck)) {
    phys_set_player_sliding_check(N(should_player_be_sliding));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_iwa_10_1) = EVT_EXIT_WALK(60, iwa_00_ENTRY_0, "iwa_10", iwa_10_ENTRY_1);
EvtScript N(EVS_ExitWalk_iwa_01_0) = EVT_EXIT_WALK(60, iwa_00_ENTRY_1, "iwa_01", iwa_01_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_10_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_01_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_RUGGED)
    Call(SetSpriteShading, SHADING_NONE)
    Call(N(SetupSlidingCheck))
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_BindSlideTriggers))
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Call(PlaySoundAtF, SOUND_LOOP_IWA00_FLOW3, SOUND_SPACE_WITH_DEPTH, 35, -80, -120)
    Call(PlaySoundAtF, SOUND_LOOP_IWA00_FLOW2, SOUND_SPACE_WITH_DEPTH, 500, 85, -120)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Call(SetTexPanner, MODEL_o949, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_water, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0, 3000,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};
