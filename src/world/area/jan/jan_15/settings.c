#include "jan_15.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_15 },
    .songVariation = 1,
    .sfxReverb = 1,
};
