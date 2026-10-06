#include "tst_20.h"

extern EvtScript EVS_Main;

EntryList Entrances = {
    [tst_20_ENTRY_0]    {    0.0,    0.0,  100.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Return
    End
};

