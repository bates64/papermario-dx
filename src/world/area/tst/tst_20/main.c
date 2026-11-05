#include "tst_20.h"

extern EvtScript EVS_Main;

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Return
    End
};
