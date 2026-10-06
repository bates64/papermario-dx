#include "kpa_114.h"

EntryList Entrances = {
    [kpa_114_ENTRY_0]   { -150.0,    0.0,  110.0,    0.0 },
    [kpa_114_ENTRY_1]   {  473.0,    0.0,  112.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_114 },
    .songVariation = 1,
    .sfxReverb = 2,
};
