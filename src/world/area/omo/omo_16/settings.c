#include "omo_16.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "omo_bg",
    .songVariation = 1,
    .sfxReverb = 2,
};
