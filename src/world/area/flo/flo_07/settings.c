#include "flo_07.h"

EntryList Entrances = {
    [flo_07_ENTRY_0]    {  375.0,    0.0,    0.0,  270.0 },
    [flo_07_ENTRY_1]    {  325.0,    0.0,    0.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "fla_bg",
    .tattle = { MSG_MapTattle_flo_07 },
};
