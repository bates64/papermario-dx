#include "pra_40.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_40_ENTRY_0]    {   13.0,    0.0,    0.0,   90.0 },
    [pra_40_ENTRY_1]    {  237.0,    0.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_40 },
    .songVariation = 1,
    .sfxReverb = 1,
};
