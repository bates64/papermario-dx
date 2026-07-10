#include "../evt_test.h"

EvtScript EVS_IfRange = {
    IfRange(LVar0, 0, 10)
        Set(LVar1, 1)
    Else
        Set(LVar1, 0)
    EndIf

    IfNotRange(LVar2, Float(0.0), Float(1.0))
        IfRange(LVar3, Float(-5.0), Float(5.0))
            Set(LVar4, 1)
        EndIf
    EndIf
    End
};
