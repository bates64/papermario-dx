#include "../evt_test.h"

EvtScript EVS_IfRangeMixedBounds = {
    IfRange(LVar0, 0, Float(100.0))
        Set(LVar1, 1)
    EndIf
    End
};
