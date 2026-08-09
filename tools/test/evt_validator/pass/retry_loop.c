#include "../evt_test.h"

EvtScript EVS_RetryLoop = {
    Set(LVar0, false)
    Loop(3)
        IfEq(LVar0, false)
            Set(LVar0, true)
            RetryLoop
        EndIf
    EndLoop
    End
};
