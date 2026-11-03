#include "tst_20.h"

extern EvtScript EVS_Main;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Return
    End
};
