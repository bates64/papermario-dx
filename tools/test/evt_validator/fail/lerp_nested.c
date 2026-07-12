#include "../evt_test.h"

EvtScript EVS_LerpNested = {
    Lerp(LVar0, 0, 10, 3, EASING_LINEAR)
        Lerp(LVar1, 0, 20, 3, EASING_LINEAR)
        EndLerp
    EndLerp
    End
};
