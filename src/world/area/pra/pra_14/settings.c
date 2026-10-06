#include "pra_14.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_14_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_14_ENTRY_1]    {   13.0,    0.0,  -70.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_14 },
    .songVariation = 1,
    .sfxReverb = 2,
};
