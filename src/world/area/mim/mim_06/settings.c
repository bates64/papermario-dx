#include "mim_06.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "obk_bg",
    .tattle = { MSG_MapTattle_mim_06 },
    .songVariation = 1,
    .sfxReverb = 2,
};
