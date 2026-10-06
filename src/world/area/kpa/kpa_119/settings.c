#include "kpa_119.h"

EntryList Entrances = {
    [kpa_119_ENTRY_0]   {    6.0,    0.0,  100.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_119 },
    .songVariation = 1,
    .sfxReverb = 1,
};
