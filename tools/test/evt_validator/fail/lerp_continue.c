#include "../evt_test.h"

EvtScript EVS_LerpContinue = {
    Lerp(LVar0, 0, 10, 3, EASING_LINEAR)
        ContinueLoop
    EndLerp
    End
};
