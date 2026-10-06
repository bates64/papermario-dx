#include "kpa_08.h"

EntryList Entrances = {
    [kpa_08_ENTRY_0]    { -483.0,    0.0,  -19.0,   90.0 },
    [kpa_08_ENTRY_1]    {  203.0,  100.0,  -22.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_08 },
    .songVariation = 1,
    .sfxReverb = 2,
};
