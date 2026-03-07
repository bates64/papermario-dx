#include "iwa_01.h"

#include "world/common/atomic/TexturePan.inc.c"

b32 N(should_player_be_sliding)(void) {
    Shadow* shadow = get_shadow_by_index(gPlayerStatus.shadowID);
    f32 angle = shadow->rot.z + 180.0;

    return (angle != 0.0f) && (gPlayerStatus.pos.x < -300.0f || gPlayerStatus.pos.x > -140.0f);
}

API_CALLABLE(N(SetupSlidingCheck)) {
    phys_set_player_sliding_check(N(should_player_be_sliding));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_iwa_00_1) = EVT_EXIT_WALK(60, iwa_01_ENTRY_0, "iwa_00", iwa_00_ENTRY_1);
EvtScript N(EVS_ExitWalk_iwa_03_0) = EVT_EXIT_WALK(60, iwa_01_ENTRY_1, "iwa_03", iwa_03_ENTRY_0);
EvtScript N(EVS_ExitWalk_iwa_02_0) = EVT_EXIT_WALK(60, iwa_01_ENTRY_2, "iwa_02", iwa_02_ENTRY_0);
EvtScript N(EVS_ExitWalk_iwa_02_1) = EVT_EXIT_WALK(60, iwa_01_ENTRY_3, "iwa_02", iwa_02_ENTRY_1);

EvtScript N(EVS_StartTexPanners) = {
    // waterfalls
    Call(SetTexPanner, MODEL_o946, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o947, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0, -3000,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,     1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,     0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // foam and splashes
    Call(SetTexPanner, MODEL_o952, TEX_PANNER_C)
    Call(SetTexPanner, MODEL_o956, TEX_PANNER_C)
    Call(SetTexPanner, MODEL_o957, TEX_PANNER_C)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_C)
        TEX_PAN_PARAMS_STEP(0x8000,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(     4,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(     0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_00_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_03_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_02_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_02_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili4, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_RUGGED)
    Call(SetSpriteShading, SHADING_NONE)
    Call(N(SetupSlidingCheck))
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_StartTexPanners))
    ExecWait(N(EVS_MakeSplashes))
    Exec(N(EVS_BindSlideTriggers2))
    Exec(N(EVS_BindSlideTriggers1))
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Call(PlaySoundAtF, SOUND_LOOP_IWA01_FLOW1, SOUND_SPACE_WITH_DEPTH, -570, -180, 425)
    Call(PlaySoundAtF, SOUND_LOOP_IWA01_FLOW2, SOUND_SPACE_WITH_DEPTH, 740, -170, 330)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(N(EVS_BindExitTriggers))
    Else
        Set(LVar0, Ref(N(EVS_BindExitTriggers)))
        Exec(EnterWalk)
    EndIf
    Wait(1)
    Return
    End
};
