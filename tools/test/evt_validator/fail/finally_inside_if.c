#include "../evt_test.h"

EvtScript EVS_FinallyInsideIf = {
    IfEq(LVar0, 0)
        Finally
            Set(LVar0, 1)
    EndIf
    End
};
