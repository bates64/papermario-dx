#include "kpa_118.h"

EntryList Entrances = {
    [kpa_118_ENTRY_0]   {  144.0,    0.0,  100.0,    0.0 },
    [kpa_118_ENTRY_1]   { -471.0,    0.0,  100.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_118 },
    .songVariation = 1,
    .sfxReverb = 2,
};
