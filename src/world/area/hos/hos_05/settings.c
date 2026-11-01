#include "hos_05.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_05 },
    .songVariation = 1,
    .sfxReverb = 2,
};
