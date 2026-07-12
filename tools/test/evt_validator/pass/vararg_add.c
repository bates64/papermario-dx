#include "../evt_test.h"

EvtScript EVS_VarargAdd = {
    Set(LVar0, 1)
    Add(LVar0, 2)
    Add(LVar1, 1, 2, 3, LVar0)
    End
};
