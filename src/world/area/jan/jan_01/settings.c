#include "jan_01.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_01 },
};
