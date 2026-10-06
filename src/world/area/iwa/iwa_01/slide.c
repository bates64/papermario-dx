#include "iwa_01.h"

API_CALLABLE(SetPlayerSliding) {
    gPlayerStatus.slideParams = script->varTablePtr[0];
    gPlayerStatus.flags |= PS_FLAG_SLIDING;
    return ApiStatus_DONE2;
}

SlideParams SlideData1 = {
    .heading = 90.0f,
    .maxDescendAccel = 0.5f,
    .launchVel = -0.5f,
    .maxDescendVel = 16.0f,
    .integrator = { 0.0, 0.0, 0.0, 0.0 },
};

SlideParams SlideData2 = {
    .heading = 270.0f,
    .maxDescendAccel = 0.5f,
    .launchVel = -0.18f,
    .maxDescendVel = 18.0f,
    .integrator = { 10.9716, -0.34, 0.003, -0.012 },
};

EvtScript EVS_UpdateSliding1 = {
    Set(LVar0, Ref(SlideData1))
    Call(SetPlayerSliding)
    Return
    End
};

EvtScript EVS_UpdateSliding2 = {
    Set(LVar0, Ref(SlideData2))
    Call(SetPlayerSliding)
    Return
    End
};

EvtScript EVS_UseSlide1 = {
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
    Call(PlayerMoveTo, -440, 60, 30)
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

EvtScript EVS_UseSlide2 = {
    Call(DisablePlayerInput, true)
    Wait(10)
    Thread
        Call(PlaySoundAtCollider, COLLIDER_st2, SOUND_IWA_SLIDE_GATE, SOUND_SPACE_DEFAULT)
        Call(MakeLerp, 0, 80, 10, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, MODEL_se2, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(15)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_st2, COLLIDER_FLAGS_UPPER_MASK)
    Call(PlayerMoveTo, 543, 50, 20)
    Call(DisablePlayerInput, false)
    Wait(100)
    Thread
        Call(PlaySoundAtCollider, COLLIDER_st2, SOUND_IWA_SLIDE_GATE, SOUND_SPACE_DEFAULT)
        Call(MakeLerp, 80, 0, 30, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, MODEL_se2, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_st2, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_BindSlideTriggers1 = {
    BindTrigger(Ref(EVS_UseSlide1), TRIGGER_WALL_PRESS_A, COLLIDER_st1, 1, 0)
    BindTrigger(Ref(EVS_UpdateSliding1), TRIGGER_FLOOR_TOUCH, COLLIDER_suberi1, 1, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_suberi1, SURFACE_TYPE_SLIDE)
    Return
    End
};

EvtScript EVS_BindSlideTriggers2 = {
    BindTrigger(Ref(EVS_UseSlide2), TRIGGER_WALL_PRESS_A, COLLIDER_st2, 1, 0)
    BindTrigger(Ref(EVS_UpdateSliding2), TRIGGER_FLOOR_TOUCH, COLLIDER_suberi01, 1, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_suberi01, SURFACE_TYPE_SLIDE)
    Return
    End
};
