#include "../evt_test.h"

EvtScript EVS_Finally = {
    IfEq(LVar0, 0)
        Return
    EndIf
    Finally
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
