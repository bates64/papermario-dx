#include "../evt_test.h"

EvtScript EVS_MixedCaseGroup = {
    Switch(0)
        CaseOrEq(0)
        CaseAndEq(1)
        EndCaseGroup
    EndSwitch
    End
};
