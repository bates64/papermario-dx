#include "../evt_test.h"

EvtScript EVS_FinallyBreakPoint = {
    Finally
        BreakPoint("cleanup")
    End
};
