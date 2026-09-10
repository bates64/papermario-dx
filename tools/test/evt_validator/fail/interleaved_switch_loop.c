#include "../evt_test.h"

EvtScript EVS_InterleavedSwitchLoop = {
    Switch(LVar0)
        CaseDefault
            Loop(1)
    EndSwitch
            EndLoop
    End
};
