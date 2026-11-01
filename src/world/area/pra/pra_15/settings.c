#include "pra_15.h"

#include "../common/MapInit_EnableFloorReflection.inc.c"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_pra_15 },
    .songVariation = 1,
    .sfxReverb = 1,
};
