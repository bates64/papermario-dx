#include "kpa_03.h"

EntryList Entrances = {
    [kpa_03_ENTRY_0]    { 1888.0, -410.0,  -93.0,  270.0 },
    [kpa_03_ENTRY_1]    { -1575.0, -105.0, -158.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_03 },
    .songVariation = 1,
    .sfxReverb = 3,
};
