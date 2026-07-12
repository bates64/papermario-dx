#include "../evt_test.h"

EvtScript EVS_ExecArgsChild = {
    ExpectArgs(5)
    End
};

EvtScript EVS_ExecArgs = {
    Set(LVar0, 12)
    SetF(LVar1, Float(1.5))
    Exec(EVS_ExecArgsChild, 7, LVar0, ARG_INT(LVar0), Float(2.5), ARG_FLOAT(LVar1))
    ExecGetTID(EVS_ExecArgsChild, LVar2, 1, ARG_INT(LVar0))
    ExecWait(EVS_ExecArgsChild, ARG_FLOAT(LVar1), Ref(EVS_ExecArgsChild))
    End
};
