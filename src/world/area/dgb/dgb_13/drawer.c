#include "dgb_13.h"

EvtScript EVS_OpenLowerDrawer = {
    Call(MakeLerp, 0, 30, 15, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, MODEL_b1, 0, 0, LVar0)
        Call(UpdateColliderTransform, COLLIDER_o265)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_CloseLowerDrawer = {
    Call(MakeLerp, 30, 0, 15, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, MODEL_b1, 0, 0, LVar0)
        Call(UpdateColliderTransform, COLLIDER_o265)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_OpenUpperDrawer = {
    Call(MakeLerp, 0, 30, 15, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, MODEL_b3, 0, 0, LVar0)
        Call(UpdateColliderTransform, COLLIDER_o267)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_CloseUpperDrawer = {
    Call(MakeLerp, 30, 0, 15, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, MODEL_b3, 0, 0, LVar0)
        Call(UpdateColliderTransform, COLLIDER_o267)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_Interact_LowerDrawer = {
    IfEq(MV_LowerDrawerOpen, false)
        ExecWait(EVS_OpenLowerDrawer)
        Set(MV_LowerDrawerOpen, true)
    Else
        ExecWait(EVS_CloseLowerDrawer)
        Set(MV_LowerDrawerOpen, false)
    EndIf
    Unbind
    Return
    End
};

EvtScript EVS_SetupDrawers = {
    Call(ParentColliderToModel, COLLIDER_o265, MODEL_o419)
    BindTrigger(Ref(EVS_Interact_LowerDrawer), TRIGGER_WALL_PRESS_A, COLLIDER_o265, 1, 0)
    Return
    End
};
