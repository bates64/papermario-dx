#include "sam_05.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sam_bg",
    .tattle = { MSG_MapTattle_sam_05 },
};
