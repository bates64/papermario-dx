#include "iwa_03.h"

b32 N(should_player_be_sliding)(void) {
    Shadow* shadow = get_shadow_by_index(gPlayerStatus.shadowID);
    f32 angle = shadow->rot.z + 180.0;

    return (angle != 0.0f) && (fabsf(angle) >= 20.0f);
}

API_CALLABLE(N(SetupSlidingCheck)) {
    phys_set_player_sliding_check(N(should_player_be_sliding));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_iwa_01_1) = EVT_EXIT_WALK(60, iwa_03_ENTRY_0, "iwa_01", iwa_01_ENTRY_1);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_iwa_01_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
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
    Exec(N(EVS_BindSlideTriggers))
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_patapata, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};
