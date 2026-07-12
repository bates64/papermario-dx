#include "../evt_test.h"

static char InvalidLabel[] = "1bad";

EvtScript EVS_InvalidLabelString = {
    Goto(InvalidLabel)
    End
};
