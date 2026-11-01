#include "sam_07.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_07 },
    .songVariation = 1,
    .sfxReverb = 1,
};
