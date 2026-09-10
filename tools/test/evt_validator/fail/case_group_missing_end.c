#include "../evt_test.h"

EvtScript EVS_CaseGroupMissingEnd = {
    Switch(0)
        CaseOrEq(0)
        CaseOrEq(1)
    EndSwitch
    End
};
