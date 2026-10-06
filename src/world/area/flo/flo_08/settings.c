#include "flo_08.h"

EntryList Entrances = {
    [flo_08_ENTRY_0]    { -870.0,    0.0,    0.0,   90.0 },
    [flo_08_ENTRY_1]    {  570.0,    0.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_08 },
};
