#include "pra_22.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_22_ENTRY_0]    {  126.0,    0.0,  137.0,    0.0 },
    [pra_22_ENTRY_1]    {  487.0, -200.0,   70.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_22 },
    .songVariation = 1,
    .sfxReverb = 2,
};
