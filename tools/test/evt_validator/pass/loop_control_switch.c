#include "../evt_test.h"

EvtScript EVS_LoopControlInsideSwitch = {
    Loop(1)
        Switch(LVar0)
            CaseEq(0)
                BreakLoop
            CaseEq(1)
                ContinueLoop
            CaseDefault
                RetryLoop
        EndSwitch
    EndLoop
    End
};

EvtScript EVS_BreakSwitchInsideLoop = {
    Switch(LVar0)
        CaseDefault
            Loop(1)
                Lerp(LVar1, 0, 10, 2, EASING_LINEAR)
                    BreakSwitch
                EndLerp
            EndLoop
    EndSwitch
    End
};
