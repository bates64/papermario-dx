#include "tst_11.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupReflections;

EvtScript EVS_Main = {
    Exec(EVS_SetupReflections)
    Return
    End
};
