#include "tst_11.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupReflections;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(EVS_SetupReflections)
    Return
    End
};
