#include "iwa_04.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "iwa_bg",
    .tattle = { MSG_MapTattle_iwa_04 },
};
