#include "kpa_96.h"

EntryList Entrances = {
    [kpa_96_ENTRY_0]    {  210.0,    0.0,  100.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_96 },
    .songVariation = 1,
    .sfxReverb = 1,
};
