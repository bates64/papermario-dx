#include "pra_29.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_29_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_29_ENTRY_1]    {  487.0,    0.0,   70.0,  270.0 },
    [pra_29_ENTRY_2]    {  487.0,    0.0,  -70.0,  270.0 },
    [pra_29_ENTRY_3]    {   13.0,    0.0,  -70.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_29 },
    .songVariation = 1,
    .sfxReverb = 2,
};
