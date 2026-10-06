#include "flo_14.h"

EntryList Entrances = {
    [flo_14_ENTRY_0]    {  720.0,    0.0,    0.0,  270.0 },
    [flo_14_ENTRY_1]    { -720.0,    0.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_14 },
};
