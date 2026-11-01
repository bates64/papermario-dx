#include "kzn_03.h"
#include "entity.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_kzn_03 },
    .songVariation = 1,
    .sfxReverb = 2,
};
