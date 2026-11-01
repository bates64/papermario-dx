#include "pra_27.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_pra_27 },
    .songVariation = 1,
    .sfxReverb = 1,
};
