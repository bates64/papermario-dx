#include "../evt_test.h"

EvtScript EVS_LoopWithoutEndLoop = {
    Loop(1)
        Wait(1)
    End
};
