#include "kmr_04.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_04 },
};
