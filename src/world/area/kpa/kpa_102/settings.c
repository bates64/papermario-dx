#include "kpa_102.h"

EntryList Entrances = {
    [kpa_102_ENTRY_0]   { -480.0,    0.0, -215.0,   90.0 },
    [kpa_102_ENTRY_1]   {  764.0,    0.0, -215.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_102 },
    .songVariation = 1,
    .sfxReverb = 3,
};
