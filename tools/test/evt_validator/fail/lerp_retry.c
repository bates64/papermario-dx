#include "../evt_test.h"

EvtScript EVS_LerpRetry = {
    Lerp(LVar0, 0, 10, 3, EASING_LINEAR)
        RetryLoop
    EndLerp
    End
};
