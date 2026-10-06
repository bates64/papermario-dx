#include "kpa_113.h"

EntryList Entrances = {
    [kpa_113_ENTRY_0]   { -208.0,    0.0,  100.0,   90.0 },
    [kpa_113_ENTRY_1]   {  408.0,    0.0,  100.0,  270.0 },
    [kpa_113_ENTRY_2]   { -102.0,    0.0,   20.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_113 },
    .songVariation = 1,
    .sfxReverb = 3,
};
