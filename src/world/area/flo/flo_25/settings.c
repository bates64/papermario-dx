#include "flo_25.h"

EntryList Entrances = {
    [flo_25_ENTRY_0]    {  620.0,    0.0,    0.0,  270.0 },
    [flo_25_ENTRY_1]    { -620.0,    0.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_25 },
};
