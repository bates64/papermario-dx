#include "dgb_02.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_dgb_02 },
    .songVariation = 1,
    .sfxReverb = 2,
};
