#include "pra_05.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_05_ENTRY_0]    {   13.0,    0.0,   75.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_05 },
    .songVariation = 1,
    .sfxReverb = 1,
};
