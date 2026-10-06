#include "kpa_70.h"

EntryList Entrances = {
    [kpa_70_ENTRY_0]    {   13.0,    0.0,  134.0,   90.0 },
    [kpa_70_ENTRY_1]    { 1233.0,    0.0,  126.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_70 },
    .songVariation = 1,
    .sfxReverb = 3,
};
