#include "arn_11.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_arn_11 },
    .songVariation = 1,
    .sfxReverb = 1,
};
