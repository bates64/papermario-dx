#include "pra_19.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_19_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_19_ENTRY_1]    {  487.0,    0.0,   70.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_19 },
    .songVariation = 1,
    .sfxReverb = 2,
};
