#include "pra_11.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

EntryList Entrances = {
    [pra_11_ENTRY_0]    {   23.0,    0.0,   81.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_pra_11 },
    .songVariation = 1,
    .sfxReverb = 1,
};
