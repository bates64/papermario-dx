#include "../evt_test.h"

EvtScript EVS_Finally = {
    IfEq(LVar0, 0)
        Return
    EndIf
    Finally
        KillScript(LVar1)
        Set(LVar0, 1)
    End
};

EvtScript EVS_ThreadFinally = {
    Thread
        IfEq(LVar0, 0)
            Return
        EndIf
        Finally
            Set(LVar0, 1)
        EndThread
    End
};

EvtScript EVS_ChildThreadFinally = {
    ChildThread
        IfEq(LVar0, 0)
            Return
        EndIf
        Finally
            Set(LVar0, 1)
        EndChildThread
    End
};

EvtScript EVS_FinallyDetachedChild = {
    End
};

EvtScript EVS_FinallyDetachedExec = {
    Finally
        Exec(EVS_FinallyDetachedChild)
        ExecGetID(LVar0, EVS_FinallyDetachedChild)
    End
};
