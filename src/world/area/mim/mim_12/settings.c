#include "mim_12.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_mim_12 },
    .songVariation = 1,
    .sfxReverb = 2,
};
