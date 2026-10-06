#include "kpa_51.h"

EntryList Entrances = {
    [kpa_51_ENTRY_0]    { -470.0,    0.0,  -28.0,   90.0 },
    [kpa_51_ENTRY_1]    {  745.0,    0.0,  -28.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_51 },
    .songVariation = 1,
    .sfxReverb = 2,
};
