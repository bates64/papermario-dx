#include "kpa_04.h"

EntryList Entrances = {
    [kpa_04_ENTRY_0]    {  212.0,    0.0,  150.0,  270.0 },
    [kpa_04_ENTRY_1]    {    0.0,    0.0,  287.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kpa_04 },
    .songVariation = 1,
    .sfxReverb = 2,
};
