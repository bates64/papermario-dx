#include "obk_08.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_obk_08 },
    .songVariation = 1,
    .sfxReverb = 1,
};
