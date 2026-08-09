#include "../evt_test.h"

EvtScript EVS_ThreadParentLoopControl = {
    Loop(1)
        Thread
            BreakLoop
        EndThread
    EndLoop
    End
};
