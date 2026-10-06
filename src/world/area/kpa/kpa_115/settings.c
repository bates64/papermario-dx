#include "kpa_115.h"

EntryList Entrances = {
    [kpa_115_ENTRY_0]   { -208.0,    0.0,  100.0,   90.0 },
    [kpa_115_ENTRY_1]   {  100.0,    0.0,   20.0,  180.0 },
    [kpa_115_ENTRY_2]   {   50.0,    0.0,   20.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_115 },
    .songVariation = 1,
    .sfxReverb = 3,
};
