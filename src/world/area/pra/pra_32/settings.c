#include "pra_32.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sam_bg",
    .tattle = { MSG_MapTattle_pra_32 },
    .songVariation = 1,
    .sfxReverb = 1,
};
