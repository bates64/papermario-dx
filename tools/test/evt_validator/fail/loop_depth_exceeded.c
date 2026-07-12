#include "../evt_test.h"

EvtScript EVS_LoopDepthExceeded = {
    Loop(1)
        Loop(1)
            Loop(1)
                Loop(1)
                    Loop(1)
                        Loop(1)
                            Loop(1)
                                Loop(1)
                                    Loop(1)
    End
};
