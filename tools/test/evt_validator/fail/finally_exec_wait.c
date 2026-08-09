#include "../evt_test.h"

EvtScript EVS_FinallyExecWait = {
    Finally
        ExecWait(EVS_FinallyExecWait)
    End
};
