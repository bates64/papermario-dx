#include "jan_06.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "jan_bg",
    .tattle = { MSG_MapTattle_jan_06 },
};
