#include "kpa_32.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kpa_32 },
    .songVariation = 1,
    .sfxReverb = 3,
};
