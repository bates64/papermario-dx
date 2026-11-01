#include "kpa_133.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_kpa_133 },
    .songVariation = 1,
    .sfxReverb = 3,
};
