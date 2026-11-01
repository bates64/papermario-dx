#include "kpa_53.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_kpa_53 },
    .songVariation = 1,
    .sfxReverb = 2,
};
