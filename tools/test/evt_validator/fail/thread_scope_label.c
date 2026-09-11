#include "../evt_test.h"

EvtScript EVS_ThreadScopeLabel = {
    Goto("Inner")
    Thread
        Label("Inner")
    EndThread
    End
};
