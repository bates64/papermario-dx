#include "pra_18.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_18_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_18_ENTRY_1]    {  737.0,    0.0,  -70.0,  270.0 },
    [pra_18_ENTRY_2]    {   13.0,    0.0,  -70.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_18 },
    .songVariation = 1,
    .sfxReverb = 2,
};
