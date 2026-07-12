#include "../evt_test.h"

EvtScript EVS_FinallyDuplicate = {
    Finally
        Set(LVar0, 1)
    Finally
        Set(LVar0, 2)
    End
};
