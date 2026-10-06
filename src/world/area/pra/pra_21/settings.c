#include "pra_21.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_21_ENTRY_0]    {  126.0,    0.0, -137.0,  180.0 },
    [pra_21_ENTRY_1]    {  487.0, -200.0,  -70.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_21 },
    .songVariation = 1,
    .sfxReverb = 2,
};
