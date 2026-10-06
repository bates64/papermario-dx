#include "flo_03.h"

EntryList Entrances = {
    [flo_03_ENTRY_0]    { -325.0,    0.0,    0.0,   90.0 },
    [flo_03_ENTRY_1]    {  325.0,    0.0,    0.0,  270.0 },
    [flo_03_ENTRY_2]    { -325.0,    0.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_03 },
};
