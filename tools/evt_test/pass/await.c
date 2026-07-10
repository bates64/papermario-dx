#include "../evt_test.h"

EvtScript EVS_AwaitWorker = {
    Wait(1)
    End
};

EvtScript EVS_Await = {
    BindItemPrompt(EVS_AwaitWorker, TRIGGER_FORCE_ACTIVATE, 0, 0, 0, 0)
    ExecGetID(EVS_AwaitWorker, LVar0)
    IsScriptRunning(LVar0, LVar1)
    SuspendScript(LVar0)
    ResumeScript(LVar0)
    KillScript(LVar0)
    AwaitScript(LVar0)
    ChildThread
        Wait(1)
    EndChildThread
    AwaitChildren
    End
};
