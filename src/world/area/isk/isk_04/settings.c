#include "isk_04.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk3_bg",
    .tattle = { MSG_MapTattle_isk_04 },
    .songVariation = 1,
    .sfxReverb = 2,
};
