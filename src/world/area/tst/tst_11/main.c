#include "tst_11.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupReflections;

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(EVS_SetupReflections)
    Return
    End
};
