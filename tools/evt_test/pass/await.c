#include "../evt_test.h"

EvtScript EVS_AwaitWorker = {
    Wait(1)
    End
};

EvtScript EVS_Await = {
    ExecGetTID(EVS_AwaitWorker, LVar0)
    AwaitScript(LVar0)
    ChildThread
        Wait(1)
    EndChildThread
    AwaitChildren
    End
};
