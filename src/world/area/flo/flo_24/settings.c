#include "flo_24.h"

EntryList Entrances = {
    [flo_24_ENTRY_0]    { -455.0,    0.0,    0.0,   90.0 },
    [flo_24_ENTRY_1]    {  455.0,    0.0,    0.0,  270.0 },
    [flo_24_ENTRY_2]    {  455.0,    0.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_24 },
};
