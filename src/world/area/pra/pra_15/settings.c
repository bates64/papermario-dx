#include "pra_15.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList N(Entrances) = {
    [pra_15_ENTRY_0]    {  487.0,  -60.0,  106.0,  270.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_pra_15 },
    .songVariation = 1,
    .sfxReverb = 1,
};
