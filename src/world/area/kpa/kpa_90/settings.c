#include "kpa_90.h"

EntryList Entrances = {
    [kpa_90_ENTRY_0]    { -470.0,    0.0,  100.0,   90.0 },
    [kpa_90_ENTRY_1]    {  265.0, -240.0,  100.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_90 },
    .songVariation = 1,
    .sfxReverb = 2,
};
