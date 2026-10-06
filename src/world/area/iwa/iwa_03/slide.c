#include "iwa_03.h"

SlideParams SlideData = {
    .heading = 89.0f,
    .maxDescendAccel = 0.41f,
    .launchVel = -0.25f,
    .maxDescendVel = 16.0f,
    .integrator = { 9.612, -0.452, 0.003, -0.023 },
};

API_CALLABLE(SetPlayerSliding) {
    gPlayerStatus.slideParams = script->varTablePtr[0];
    gPlayerStatus.flags |= PS_FLAG_SLIDING;
    return ApiStatus_DONE2;
}

EvtScript EVS_UpdateSliding = {
    Set(LVar0, Ref(SlideData))
    Call(SetPlayerSliding)
    Return
    End
};

EvtScript EVS_UseSlide = {
    Call(DisablePlayerInput, true)
    Wait(10)
    Thread
        Call(PlaySoundAtCollider, COLLIDER_st1, SOUND_IWA_SLIDE_GATE, SOUND_SPACE_DEFAULT)
        Call(MakeLerp, 0, -80, 10, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, MODEL_se1, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(15)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_st1, COLLIDER_FLAGS_UPPER_MASK)
    Call(SetPlayerSpeed, Float(3.0))
    Call(PlayerMoveTo, -1460, -60, 0)
    Call(DisablePlayerInput, false)
    Wait(100)
    Thread
        Call(PlaySoundAtCollider, COLLIDER_st1, SOUND_IWA_SLIDE_GATE, SOUND_SPACE_DEFAULT)
        Call(MakeLerp, -80, 0, 30, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, MODEL_se1, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_st1, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_BindSlideTriggers = {
    BindTrigger(Ref(EVS_UseSlide), TRIGGER_WALL_PRESS_A, COLLIDER_st1, 1, 0)
    BindTrigger(Ref(EVS_UpdateSliding), TRIGGER_FLOOR_TOUCH, COLLIDER_suberi0, 1, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_suberi0, SURFACE_TYPE_SLIDE)
    Return
    End
};
