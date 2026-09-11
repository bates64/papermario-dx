#include "../evt_test.h"

EvtScript EVS_IfNotRangeMixedBounds = {
    IfNotRange(LVar0, Float(0.0), 100)
        Set(LVar1, 1)
    EndIf
    End
};
