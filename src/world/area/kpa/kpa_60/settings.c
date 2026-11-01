#include "kpa_60.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kpa_62 },
};
