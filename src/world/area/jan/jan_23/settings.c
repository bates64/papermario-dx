#include "jan_23.h"

EntryList Entrances = {
    [jan_23_ENTRY_0]    {  230.0,  160.0,  106.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_23 },
};
