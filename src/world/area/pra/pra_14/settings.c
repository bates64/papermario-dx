#include "pra_14.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_pra_14 },
    .songVariation = 1,
    .sfxReverb = 2,
};
