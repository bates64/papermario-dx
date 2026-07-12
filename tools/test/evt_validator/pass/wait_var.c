#include "../evt_test.h"

EvtScript EVS_WaitVar = {
    Set(LVar0, 1)
    Wait(LVar0)
    End
};
