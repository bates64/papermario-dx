#include "../evt_test.h"

EvtScript EVS_SwitchWithoutEndSwitch = {
    Switch(0)
        CaseDefault
            Wait(1)
    End
};
