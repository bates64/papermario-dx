#include "../evt_test.h"

EvtScript EVS_IfWithoutEndIf = {
    IfEq(0, 0)
        Wait(1)
    End
};
