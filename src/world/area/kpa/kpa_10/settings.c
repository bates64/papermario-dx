#include "kpa_10.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_kpa_10 },
    .songVariation = 1,
    .sfxReverb = 3,
};
