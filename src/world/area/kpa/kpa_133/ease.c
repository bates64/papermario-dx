#include "kpa_133.h"

EvtScript N(EVS_OnHitSwitch) = {
    Call(MakeLerp, 0, 90, 45, EASING_COS_FAST_OVERSHOOT)
    Label(10)
        Call(UpdateLerp)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(10)
        EndIf
    Unbind
    Return
    End
};
