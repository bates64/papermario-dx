#include "../evt_test.h"

EvtScript EVS_ContinueLoop = {
    Loop(3)
        ContinueLoop
    EndLoop
    End
};
