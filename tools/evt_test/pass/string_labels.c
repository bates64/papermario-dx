#include "../evt_test.h"

EvtScript EVS_StringLabels = {
    Goto("Resume")
    Label("Skip")
    Wait(1)
    Label("Resume")
    Goto("Skip")
    End
};
