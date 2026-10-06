#include "iwa_02.h"

EntryList Entrances = {
    [iwa_02_ENTRY_0]    { -172.0,    0.0,  164.0,   90.0 },
    [iwa_02_ENTRY_1]    { -194.0,  238.0,  238.0,   90.0 },
    [iwa_02_ENTRY_2]    { 1183.0,  288.0,   60.0,  270.0 },
    [iwa_02_ENTRY_3]    { 1231.0,   50.0,  243.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_02 },
};
