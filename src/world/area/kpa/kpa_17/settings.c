#include "kpa_17.h"

EntryList Entrances = {
    [kpa_17_ENTRY_0]    { 1042.0,  250.0, -496.0,   90.0 },
    [kpa_17_ENTRY_1]    { 1168.0,   30.0, -560.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_17 },
    .songVariation = 1,
    .sfxReverb = 2,
};
