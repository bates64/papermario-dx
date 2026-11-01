#include "kzn_20.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_kzn_20 },
    .songVariation = 1,
    .sfxReverb = 2,
};
