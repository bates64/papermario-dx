#include "kpa_95.h"

EntryList Entrances = {
    [kpa_95_ENTRY_0]    {  205.0,    0.0,  100.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_95 },
    .songVariation = 1,
    .sfxReverb = 2,
};
