#include "../evt_test.h"

extern char MissingLabel[];

EvtScript EVS_UnresolvedStringLabel = {
    Goto(MissingLabel)
    End
};
