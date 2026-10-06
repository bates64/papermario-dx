#include "iwa_00.h"

EntryList Entrances = {
    [iwa_00_ENTRY_0]    {   55.0,   -5.0,  -25.0,   90.0 },
    [iwa_00_ENTRY_1]    { 1313.0,   90.0,  -40.0,  270.0 },
    [iwa_00_ENTRY_2]    {  625.0,  -30.0,  259.0,   45.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_00 },
};
