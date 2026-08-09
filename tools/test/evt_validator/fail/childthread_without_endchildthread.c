#include "../evt_test.h"

EvtScript EVS_ChildThreadWithoutEndChildThread = {
    ChildThread
        Wait(1)
    End
};
