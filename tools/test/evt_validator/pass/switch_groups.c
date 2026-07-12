#include "../evt_test.h"

EvtScript EVS_SwitchGroups = {
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(1)
            EndCaseGroup
        CaseEq(2)
            BreakSwitch
        CaseDefault
    EndSwitch
    End
};
