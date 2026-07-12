#include "../evt_test.h"

EvtScript EVS_BasicFlow = {
    IfEq(0, 0)
        Loop(1)
            BreakLoop
        EndLoop
    Else
        Wait(1)
    EndIf
    End
};
