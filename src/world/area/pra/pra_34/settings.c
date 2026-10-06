#include "pra_34.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_34_ENTRY_0]    {   13.0,    0.0,   70.0,   90.0 },
    [pra_34_ENTRY_1]    {  237.0,    0.0,   70.0,  270.0 },
    [pra_34_ENTRY_2]    {  237.0,    0.0,  -70.0,  270.0 },
    [pra_34_ENTRY_3]    {   13.0,    0.0,  -70.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_34 },
    .songVariation = 1,
    .sfxReverb = 1,
};
