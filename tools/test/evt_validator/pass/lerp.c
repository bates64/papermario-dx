#include "../evt_test.h"

EvtScript EVS_Lerp = {
    Lerp(LVar0, 0, 10, 3, EASING_LINEAR)
        Add(LVar1, LVar0)
    EndLerp

    Loop(2)
        Lerp(LVar1, Float(0.0), Float(1.0), 2, EASING_COS_IN_OUT)
            BreakLoop
        EndLerp
    EndLoop
    End
};
