#include "pra_31.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_31_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_31_ENTRY_1]    {  487.0,   50.0,   13.0,  270.0 },
    [pra_31_ENTRY_2]    {   13.0,    0.0,  -70.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_31 },
    .songVariation = 1,
    .sfxReverb = 2,
};
