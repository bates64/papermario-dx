#include "sam_09.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yki_bg",
    .tattle = { MSG_MapTattle_sam_09 },
    .songVariation = 1,
    .sfxReverb = 1,
};
