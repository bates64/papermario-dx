#include "omo_10.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "omo_bg",
    .tattle = { MSG_MapTattle_omo_10 },
    .songVariation = 1,
    .sfxReverb = 2,
};
