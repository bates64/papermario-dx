#include "flo_15.h"

EntryList Entrances = {
    [flo_15_ENTRY_0]    {  320.0,    0.0,    0.0,  270.0 },
    [flo_15_ENTRY_1]    { -170.0,    0.0,   55.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_15 },
};
