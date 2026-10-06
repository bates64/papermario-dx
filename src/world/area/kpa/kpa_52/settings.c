#include "kpa_52.h"

EntryList Entrances = {
    [kpa_52_ENTRY_0]    { -345.0,    0.0,  -80.0,   90.0 },
    [kpa_52_ENTRY_1]    {  330.0,    0.0,  -25.0,  270.0 },
    [kpa_52_ENTRY_2]    {  330.0,  119.0, -140.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_52 },
    .songVariation = 1,
    .sfxReverb = 2,
};
