#include "flo_18.h"

EntryList Entrances = {
    [flo_18_ENTRY_0]    { -320.0,    0.0,    0.0,   90.0 },
    [flo_18_ENTRY_1]    {   36.0,    0.0,   40.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_18 },
};
