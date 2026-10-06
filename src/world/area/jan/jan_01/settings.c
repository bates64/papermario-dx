#include "jan_01.h"

EntryList Entrances = {
    [jan_01_ENTRY_0]    { -663.0,  -14.0,   53.0,   90.0 },
    [jan_01_ENTRY_1]    {  663.0,  -16.0,   40.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_01 },
};
