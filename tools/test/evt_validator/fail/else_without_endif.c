#include "../evt_test.h"

EvtScript EVS_ElseWithoutEndIf = {
    IfEq(0, 0)
    Else
        Wait(1)
    End
};
