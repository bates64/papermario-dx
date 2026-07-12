#include "../evt_test.h"

EvtScript EVS_TestChild = {
    Wait(1)
    End
};

EvtScript EVS_ThreadAndExec = {
    Thread
        Label("Worker")
        Goto("Worker")
    EndThread
    ChildThread
        Label(7)
        Goto(7)
    EndChildThread
    Call(EVT_TestDummyCall)
    Exec(EVS_TestChild)
    ExecWait(EVS_TestChild)
    End
};
