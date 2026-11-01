#include "dgb_15.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_dgb_15 },
    .songVariation = 1,
    .sfxReverb = 2,
};
