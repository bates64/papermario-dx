#include "../evt_test.h"

EvtScript EVS_CaseBeforeEndCaseGroup = {
    Switch(0)
        CaseOrEq(0)
        CaseEq(1)
    EndSwitch
    End
};
