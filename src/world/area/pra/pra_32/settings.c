#include "pra_32.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList N(Entrances) = {
    [pra_32_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "sam_bg",
    .tattle = { MSG_MapTattle_pra_32 },
    .songVariation = 1,
    .sfxReverb = 1,
};
