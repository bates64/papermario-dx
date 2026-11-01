#include "pra_39.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_pra_39 },
    .songVariation = 1,
    .sfxReverb = 2,
};
